## 1.0.83
* change mysql queries to work for newer mysql versions
* make sqlite work properly
* some changes to skillsets to work properly
* better handling for sql injections
* try to fix multiple names on same steamid when saving by steamid
* fix giving max level to players who connect before 3 seconds passed after a map starts
* add NoNameChange plugin to avoid the hassle of checking name changing and exploits using name change
* fix that some sounds would not be preloaded
* fix not being able to mend or cure fire (shopmenu3) from napalm and flamethrower (flame strike)
* fix flamethrower being able to stack burns
* fix flamethrower persisting after death
* fix not being able to have napalm burn and flamethrower burn in the same time
* optimize napalm burn and flamethrower burn tasks and stop them at the start of a new round
* buff flamethrower to start burning after 1.5 seconds from 3.5 seconds
* buff flamethrower to run until mended or cured or dead
* streamline mend text and exp
* fix that rot didn't work
* fix uninteded stacking of dots, even over rounds
* fix flamethrower hitting allies even with friendly fire off
* fix admin skills only not loading properly at login and from skillset
* fix ultimates loading properly after a skillset load
* whois now properly shows the ultimates and enhancement xp of the target and not yourself
* whois and charsheet commands now use the same underlying function
* try to fix bots picking illegal skills
* phoenix is now 15%, 35%, 55%, 75%, 100% from 25%, 50%, 75%, 100%, 125%
* blink is now 10%, 25%, 40%, 55%, 75%, 100% from 0%, 15%, 30%, 45%, 60%, 75%
* evasion is now 2%, 3%, 5%, 7%, 11%, 14%, 18% from 7%, 8%, 9%, 10%, 11%, 12%, 13%
* dex gives 1% to evasion instead of 2%
* show all values for intelligence and wisdom
* small improvement to commands info menu not fitting all lines
* fixed resistance info
* add better skill info with computed values
* fix critical strike dealing triple damage instead of double
* fix phoenix working multiple times per round from the same player