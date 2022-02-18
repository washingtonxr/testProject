##This is Read me File.

Content of launch.json
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "g++ - Build and debug active file",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/cppTest",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "Build",
            "miDebuggerPath": "/usr/bin/gdb"
        }
    ]
}

Content of settings.json
{
    "files.associations": {
        "ostream": "cpp",
        "iostream": "cpp"
    }
}

Content of tasks.json
{
    "options": {
        "cwd": "${workspaceFolder}/build"
    },
    "tasks": [
        {
            "type": "shell",
            "label": "cmake",
            "command": "cmake",
            "args": [
                ".."
            ]
        },
        {
            "label": "make",
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "command":"make",
            "args": []
        },
        {
            "label": "Build",
            "dependsOrder": "sequence",
            "dependsOn":[
                "cmake",
                "make"
            ]
        }
    ],
    "version": "2.0.0"
}