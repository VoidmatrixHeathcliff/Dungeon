# 文件目录

+ 客户端

```
- DungeonClient.exe
- assets
    - skins [人物皮肤贴图目录]
        - Alex
            - config.json [描述皮肤元信息]
            - walk_1.png
            - wall_2.png
            - idle_1.png
            ...
        - Steve
            - config.json
            - walk_1.png
            ...
    - audio [音频目录]
        - config.json [描述音频元信息]
        - bgm.mp3
        ...
    - fonts [字体目录]
        - config,json [描述字体元信息]
        - title.ttf
        ...
    - lang [多语言支持目录]
        - config.json [描述翻译文件元信息]
        - ch_zn.json
        - en_us.json
        ...

- maps [地图目录]
    - Wormhole
        - config.json [描述地图元信息]
        - rules.lua [描述地图生成规则]
        - tile_1.png
        - tile_2.png
        ...
    - Palace
        - config.json
        - rules.lua
        - tile_1.png
        ...
- mods [模组目录]
    - MoreWeapons
        - config.json [描述模组元信息]
        - MoreWeapons.lua [同名脚本作为入口脚本]
        - Item.lua [开发者自定义脚本等]
        ...
    - MagicalRewards
        - config.json
        - MagicalRewards.lua
        ...
- saves [游戏存档目录]
    - 2021_11_30_21_37_4728137462.sav [存档时间和id命名]
- logs [日志目录]
    - 2021_12_01_08_55_1275674.txt [日志时间和id命名]
```

+ 服务端

```
DungeonServer.exe
```