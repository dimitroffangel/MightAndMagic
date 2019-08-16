[33mcommit 7702af56c6c12473e07226746eeb58b6f3e4c9f4[m[33m ([m[1;36mHEAD -> [m[1;32mmaster[m[33m, [m[1;31morigin/master[m[33m)[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Thu Aug 15 17:18:22 2019 +0300

    Marksmen are working

[33mcommit 82b393a5136e9e32138f13cc9467bb8d71693c5e[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Thu Aug 15 15:11:52 2019 +0300

    fixed a bug, where you could press some keys once, but the effect was more than once

[33mcommit 06285395a2f17fb59c13f25be781afdc8e0f1265[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Thu Aug 15 13:10:50 2019 +0300

    Battle system is working now

[33mcommit c120802b8ae31ca6ea247bc135370d12d3a084a4[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Wed Aug 14 19:12:21 2019 +0300

    Could not commit all the info, sorry again. TryMovingOn is a function, that is trying to move the battalion on the shortest road to the found target. DistaneBetween() is calculating the distance between two points, ContainsCreature() searches all battalions on the battlefield to see if some battalion is on the eventual shortest road. In the creature class I have added a container that posses all route and there is a new function there, with which you can a new position to the route and there is a target Creature ofcoure

[33mcommit 9356eb5c0b5733d3ba2dc245ed040092327b4375[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Wed Aug 14 19:08:27 2019 +0300

    sorry for the breif info, along side that I have added several helping functions which are private in Battlefield class and some are in the Creature class

[33mcommit 2fc3c6730662047c59433844b495c9a2634a5ffd[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Wed Aug 14 19:07:10 2019 +0300

    Created BFS for AI battalions to attack enemy units

[33mcommit 42ecc5aa3a663cfc5431a813a5ec10a7ef32ca05[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Wed Aug 14 15:28:00 2019 +0300

    every bot battalion now has a target

[33mcommit f41cab844f1a338ed9e8d88307c6c5bae802bda5[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Wed Aug 14 12:40:10 2019 +0300

    when instantiating dynamic creatures, there was no virtual destructor...

[33mcommit 638c04a6e24bc242a80ba8432733ad9b706079c3[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Wed Aug 14 11:34:52 2019 +0300

    changed in the  battlefield class m_CommanderOne and Two with attacker and defender

[33mcommit ef92f88c34f7b1cf0a4a0eac33bbdb2e1cc9fa94[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Tue Aug 13 13:46:53 2019 +0300

    Heroes are deleted from the map VISUALLY

[33mcommit c9d8553d1bde2b3d5c1d7f37788130fa20a68aef[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Tue Aug 13 13:02:20 2019 +0300

     Hero is disconnected from the map if it dies

[33mcommit 91336329cf057077bf9f3096d6e141790edf17ec[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Tue Aug 13 10:49:11 2019 +0300

     fixed warnings

[33mcommit 38056f102064bba2a09a48a54122b44c1e42618e[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Tue Aug 13 10:22:33 2019 +0300

    after running from battle you can go again

[33mcommit 6294955246d99dd3f3827328d65089c49632f33d[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Tue Aug 13 09:53:41 2019 +0300

    battle will end after the last minion is down

[33mcommit 9b6ed09bfb58d728174e0638dc1d95a9266edc68[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Sun Aug 11 18:04:57 2019 +0300

    renamed BattalionNumber to BattalionSize and the function from which you can return it to GetNumberofBattalions

[33mcommit 15569c7024ee3d32180a6196c707b817aa837b4d[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Sun Aug 11 17:46:22 2019 +0300

    On retreating from the battlefield the map is restored

[33mcommit f95919edcc6af75bfdfbc289bcc73b899d1888e5[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Thu Aug 8 12:05:47 2019 +0300

    can return the player to the same position he was on battle forfeit

[33mcommit 7ec49b0409038a5c2c370a3ee0f6195efcd25808[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Thu Aug 8 12:02:30 2019 +0300

    There was undefined behaviour because I was releasing the pointer before I have finished doing all the things to it, actually I was telling the compiler, do not call the destructor on this pointer...

[33mcommit f83d32fe1e74ee4c827e78fa6067e15eb71e1dd3[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Thu Aug 8 11:59:24 2019 +0300

    The battlefield can be cleared and the battle can be on theory forfeit

[33mcommit 1b650b195a5157fd0b1d2b163ac84eb764a90e73[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Thu Aug 8 11:19:25 2019 +0300

    the enemy can attack as well during battle

[33mcommit f4116287f13c02ac6e2e31ec4620c90d7a747ba2[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Sun Aug 4 16:15:27 2019 +0300

    removed the comment

[33mcommit cba58071072cfaaa18f3d7bee43067d778da0b49[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Sun Aug 4 16:11:49 2019 +0300

    testing VS GIT with a comment in Angel.h

[33mcommit 5ff3dd752ec27d4dca4b449eb06b12dd861faaf6[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Sun Aug 4 16:10:13 2019 +0300

    testing

[33mcommit da9818c2b2af5bb1f40f340027e544a17596468c[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Sun Aug 4 16:07:36 2019 +0300

    testing git in the main working place, with a comment in Angel.h

[33mcommit dcc9b42814d936e9205a0e10b8c8d797d46d74ad[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Sun Aug 4 13:34:26 2019 +0300

    Testing to see if git is working

[33mcommit 2ef0616659ea93bdc90c5b57c74d8fc50563aa22[m
Author: dimitroffangel <angeldimitrov05@gmail.com>
Date:   Sun Aug 4 13:33:41 2019 +0300

    added "stdexcept" library to some files, in order the compilers to accept some throwing functions, cuz not all compilers will read it properly (it seems)

[33mcommit 7bbc404637cd0d942d83d9d0c3131f124de51a81[m
Author: Angel Dimitrov <angeldimitrov05@gmail.com>
Date:   Sun Aug 4 08:11:53 2019 +0300

    did some invisible changes to the Dragon

[33mcommit b2dc6747123c680b35643eea9b583b0c87f896f8[m
Author: Angel Dimitrov <angeldimitrov05@gmail.com>
Date:   Sat Aug 3 19:59:41 2019 +0300

    added a comment in dragon.h

[33mcommit da85795276c79469bec72c82f5a2bcf7caf1249b[m
Author: Angel Dimitrov <angeldimitrov05@gmail.com>
Date:   Sat Aug 3 19:44:57 2019 +0300

    recreateThings

[33mcommit a85c1f605553baafcd2261eb2e807a9a612b0a86[m
Author: Angel Dimitrov <angeldimitrov05@gmail.com>
Date:   Sat Aug 3 19:38:40 2019 +0300

    please
