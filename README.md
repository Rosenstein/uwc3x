## Install
* copy folders "addons", "sound", "sprites", "models" to your "cstrike" folder
* edit the "UWC3X.cfg" config file from "cstrike\addons\amxmodx\configs\uwc3x\UWC3X.cfg" with your preferred confiurations for things like database, XP save by name or steamid and others
* insert at the bottom of "plugins.ini" config file from "cstrike\addons\amxmodx\configs\plugins.ini" the following:
```
uwc3x.amxx
crx_nonamechange.amxx
```

## Notes
Right now it needs more testing, but hopefully none of the changes from the original will break anything.

It is recommended to save XP per name, steamid saving still needs testing.

The additional addon that doesn't let you change your name while inside the server fixes possible exploits that can copy others XP/data, they should only happen if XP is saved per name.

## License
As the [original work](https://code.google.com/p/uwc3x) follows the [GNU GPL v2](http://www.gnu.org/licenses/old-licenses/gpl-2.0.html) this is under [GNU GPL v3](http://www.gnu.org/licenses/gpl-3.0.html).
