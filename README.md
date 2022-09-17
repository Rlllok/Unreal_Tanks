# Unreal Engine 5 - Tanks

A little game developed using Unreal Engine 5. In this game you control a tank and the goal is to destroy all turrets.

Mechanics:
* Base Pawn class - In this base class implements fire, destruction and turret rotation mechanics. This is a parent class of Tank and Turret class.
* Tank Class - a Pawn that a player controls. Pawn movement was implimanted in this class.
* Turret Class - A Pawn controlled by AI. The turret fires at the player's tank if it in the attack range.
* Projectile Class - An Actor that Tank and Turret spawns when fires. This Actor deals damage.
* Health Component - a Component that takes damage from projectiles. Used by Tank and Turrets.
* Game Mode Class - A Game Mode that keeps track of whether player is alive and whether there there are turrets left. If player dies, the game ends with a lose screen. If all turrets are destroyed, then the game ends with a win screen.