if (typeof(Module) === "undefined") Module = {};
Module["arguments"] = ['--run', 'script.praat'];
Module["preRun"] = function() {
	FS.writeFile('script.praat', ['Create Sound as pure tone: "tone", 1, 0, 0.4, 44100, 440, 0.2, 0.01, 0.01',
'To Pitch: 0, 75, 600',
'Get mean: 0, 0, "Hertz"'].join('\n'));
};
