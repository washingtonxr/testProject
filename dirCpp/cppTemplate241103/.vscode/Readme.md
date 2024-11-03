Visual Studio Code provides several predefined variables you can use in your configuration files, such as tasks.json, launch.json, and others. These variables help make your configurations more flexible by adapting to the current file or workspace context. Here are some commonly used predefined variables:

${workspaceFolder}: The path of the workspace folder currently open in VS Code. If you have multiple workspace folders open, you might need to specify which one.

${file}: The full path of the currently opened file.

${fileWorkspaceFolder}: The workspace folder for the current file. Useful in a multi-root workspace.

${relativeFile}: The path of the currently opened file relative to the workspace folder.

${fileBasename}: The file name with extension (e.g., file.ext) of the currently opened file.

${fileBasenameNoExtension}: The file name without extension (e.g., file) of the currently opened file.

${fileExtname}: The file extension (e.g., .ext) of the currently opened file.

${fileDirname}: The directory name of the currently opened file.

${cwd}: The current working directory on startup of Code.

${lineNumber}: The current selected line number in the active file.

${selectedText}: The currently selected text in the active file.

${execPath}: The path to the running instance of VS Code.

When using these variables, ensure they are appropriate for your project's structure and specific configuration requirements. They help make your build and debug tasks more adaptable to changing file contexts without needing to modify the configuration each time.