if (typeof(Module) === "undefined") Module = {};
Module["arguments"] = ['--run', 'script.praat'];
Module["preRun"] = function() {
	FS.writeFile('script.praat', "writeInfoLine: \"Yo yo\"\n");
};
