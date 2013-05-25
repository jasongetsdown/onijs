{
    "targets": [
    {
        "target_name": "onijs",
        "sources": [
            "src/main.cpp"],
        "include_dirs": [ "./src/Include"],

        "libraries": ["-lOpenNI2", "-L/Users/jrossitto/code/lib/OpenNI-2.1.0/Redist", "-Wl,-rpath ./"]
    }
  ]
}