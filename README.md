build

```
cd ./qt_webengine_load_img_test
cmake -S . -B build 
cmake --build build
```

run test

```
env QTWEBENGINE_REMOTE_DEBUGGING=12345 ./build/test
```

then open remote url in chrome <http://127.0.0.1:12345>