# 42-philosophers
This version (hopefully :)) works correctly. Because I wasn't able to solve issues with my own previous version,
I took inspiration from 42 student mcombeau's implementation. Kudos to her!

Changelog:
- added INT_MAX protection;
- there is now only one watcher thread (instead on for each philo);
- less spaghetti code;
- added extra wait time for certain conditions (odd philos, etc.).
