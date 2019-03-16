# teb-husky
Contains the navigation package with all the tuned parameters for running teb on husky.

To run teb in husky:

```
roslaunch igvc_navigation move_base.launch
```

The goal should be provided in the base_link frame instead of the default odom frame of the bot.

## If husky data is not in your terminal even after connecting to the wifi the following should be added in /etc/hosts of your system

```
192.168.131.11 cpr-nuge09
```
