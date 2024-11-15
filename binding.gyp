{
"targets": [
{
"target_name": "multihashing",
"sources": ["multihashing.cc"],
"cflags": ["-std=c++17", "-fpermissive"],
"cflags_cc": ["-std=c++17", "-fpermissive"],
"include_dirs": [
"<!(node -p \"require('node-addon-api').include\")"
],
"defines": ["NAPI_VERSION=3"],
"dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],
"link_settings": {
"libraries": []
}
}
]
}
