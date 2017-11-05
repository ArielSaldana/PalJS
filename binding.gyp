{
  "targets": [
    {
      "target_name": "PalAuth",
      "sources" : [  
        "bindings/bind.cpp",
        "bindings/ecrypt.c",
        "bindings/palringo-auth.cpp"
      ],
      "include_dirs": [
            "include", "bindings",
      ],
      "cflags_cc": [ "-fexceptions" ],
      "cflags": [ "-std=c++11"],
      "conditions": [
        [ "OS=='mac'", {
          "xcode_settings": {
            "OTHER_CFLAGS": [
              "-fexceptions",
              "-lcrypto",
              "-frtti",
            ],
          },
        },
        ],
      ]
    }
  ]
}
