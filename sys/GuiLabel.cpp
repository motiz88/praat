/* GuiLabel.cpp
 *
 * Copyright (C) 1993-2012,2013,2015 Paul Boersma, 2007 Stefan de Konink
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "GuiP.h"

Thing_implement (GuiLabel, GuiControl, 0);

#if gtk
	#define iam_label  GuiLabel me = (GuiLabel) _GuiObject_getUserData (widget)
#elif cocoa
	#define iam_label  GuiLabel me = (GuiLabel) [(GuiCocoaLabel *) widget userData];
#elif motif
	#define iam_label  GuiLabel me = (GuiLabel) widget -> userData
#endif

#if gtk
	static void _GuiGtkLabel_destroyCallback (GuiObject widget, gpointer void_me) {
		(void) widget;
		iam (GuiLabel);
		forget (me);
	}
#elif cocoa
	@implementation GuiCocoaLabel {
		GuiLabel d_userData;
	}
	- (void) dealloc {   // override
		GuiLabel me = d_userData;
		forget (me);
		trace (U"deleting a label");
		[super dealloc];
	}
	- (GuiThing) getUserData {
		return d_userData;
	}
	- (void) setUserData: (GuiThing) userData {
		Melder_assert (userData == nullptr || Thing_isa (userData, classGuiLabel));
		d_userData = static_cast <GuiLabel> (userData);
	}
	@end
#elif win
	void _GuiWinLabel_destroy (GuiObject widget) {
		iam_label;
		_GuiNativeControl_destroy (widget);
		forget (me);   // NOTE: my widget is not destroyed here
	}
#elif mac
	void _GuiMacLabel_destroy (GuiObject widget) {
		iam_label;
		_GuiNativeControl_destroy (widget);
		forget (me);   // NOTE: my widget is not destroyed here
	}
#endif

GuiLabel GuiLabel_create (GuiForm parent, int left, int right, int top, int bottom,
	const char32 *labelText, uint32 flags)
{
	autoGuiLabel me = Thing_new (GuiLabel);
	my d_shell = parent -> d_shell;
	my d_parent = parent;
	#if gtk
		my d_widget = gtk_label_new (Melder_peek32to8 (labelText));
		_GuiObject_setUserData (my d_widget, me.get());
		my v_positionInForm (my d_widget, left, right, top, bottom, parent);
		g_signal_connect (G_OBJECT (my d_widget), "destroy", G_CALLBACK (_GuiGtkLabel_destroyCallback), me.get());
		gtk_misc_set_alignment (GTK_MISC (my d_widget), flags & GuiLabel_RIGHT ? 1.0 : flags & GuiLabel_CENTRE ? 0.5 : 0.0, 0.5);
	#elif cocoa
		trace (U"create");
        GuiCocoaLabel *label = [[GuiCocoaLabel alloc] init];
		my d_widget = label;
		trace (U"position");
		my v_positionInForm (my d_widget, left, right, top, bottom, parent);
		trace (U"set user data");
		[label setUserData: me.get()];
		trace (U"set bezel style");
		[label setBezelStyle: NSTextFieldRoundedBezel];
		trace (U"set bordered");
		[label setBordered: NO];
		trace (U"set selectable");
		[label setSelectable: NO];
		trace (U"title");
		[label setTitleWithMnemonic: (NSString *) Melder_peek32toCfstring (labelText)];
        [label setAlignment:( flags & GuiLabel_RIGHT ? NSRightTextAlignment : flags & GuiLabel_CENTRE ? NSCenterTextAlignment : NSLeftTextAlignment )];
		static NSFont *theLabelFont;
		if (! theLabelFont) {
			theLabelFont = [NSFont systemFontOfSize: 13.0];
		}
		[label setFont: theLabelFont];
	#elif win
		my d_widget = _Gui_initializeWidget (xmLabelWidgetClass, parent -> d_widget, labelText);
		_GuiObject_setUserData (my d_widget, me.get());
		my d_widget -> window = CreateWindow (L"static", Melder_peek32toW (_GuiWin_expandAmpersands (my d_widget -> name)),
			WS_CHILD
			| ( flags & GuiLabel_RIGHT ? SS_RIGHT : flags & GuiLabel_CENTRE ? SS_CENTER : SS_LEFT )
			| SS_CENTERIMAGE,
			my d_widget -> x, my d_widget -> y, my d_widget -> width, my d_widget -> height,
			my d_widget -> parent -> window, (HMENU) 1, theGui.instance, nullptr);
		SetWindowLongPtr (my d_widget -> window, GWLP_USERDATA, (LONG_PTR) my d_widget);
		SetWindowFont (my d_widget -> window, GetStockFont (ANSI_VAR_FONT), false);
		my v_positionInForm (my d_widget, left, right, top, bottom, parent);
	#elif mac
		my d_widget = _Gui_initializeWidget (xmLabelWidgetClass, parent -> d_widget, labelText);
		_GuiObject_setUserData (my d_widget, me.get());
		ControlFontStyleRec macFontStyleRecord = { 0 };   // BUG: _GuiNativeControl_setFont will reset alignment (should do inheritance)
		macFontStyleRecord. flags = kControlUseFontMask | kControlUseSizeMask | kControlUseJustMask;
		macFontStyleRecord. font = systemFont;
		macFontStyleRecord. size = 13;
		macFontStyleRecord. just = ( flags & GuiLabel_RIGHT ? teFlushRight : flags & GuiLabel_CENTRE ? teCenter : teFlushLeft );
		CreateStaticTextControl (my d_widget -> macWindow, & my d_widget -> rect, nullptr, & macFontStyleRecord, & my d_widget -> nat.control.handle);
		Melder_assert (my d_widget -> nat.control.handle);
		SetControlReference (my d_widget -> nat.control.handle, (long) my d_widget);
		my d_widget -> isControl = true;
		_GuiNativeControl_setTitle (my d_widget);
		my v_positionInForm (my d_widget, left, right, top, bottom, parent);
	#endif
	return me.transfer();
}

GuiLabel GuiLabel_createShown (GuiForm parent, int left, int right, int top, int bottom,
	const char32 *labelText, uint32 flags)
{
	GuiLabel me = GuiLabel_create (parent, left, right, top, bottom, labelText, flags);
	GuiThing_show (me);
	return me;
}

void GuiLabel_setText (GuiLabel me, const char32 *text /* cattable */) {
	#if gtk
		gtk_label_set_text (GTK_LABEL (my d_widget), Melder_peek32to8 (text));
	#elif cocoa
		[(NSTextField *) my d_widget setTitleWithMnemonic: (NSString *) Melder_peek32toCfstring (text)];
	#elif motif
		Melder_free (my d_widget -> name);
		my d_widget -> name = Melder_dup_f (text);
		_GuiNativeControl_setTitle (my d_widget);
	#endif
}

/* End of file GuiLabel.cpp */
