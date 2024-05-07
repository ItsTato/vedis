# Patching up Vedis!

The following pull requests from the redis repository have been added in to vedis as well.
Thanks to all the REDIS contributors! <3

### During April 21st -- April 22nd
The following patches were applied:

- [[#13133](https://github.com/redis/redis/pull/13133/)] Allocate Lua VM code with jemalloc instead of libc, and count it used memory
- [[#13195](https://github.com/redis/redis/pull/13195/)] redis-cli - sendReadOnly() to work with Redis Cloud
- [[#13183](https://github.com/redis/redis/pull/13183/)] Use usleep() instead of sched_yield() to yield cpu
- [[#13191](https://github.com/redis/redis/pull/13191/)] Fix daylight race condition and some thread leaks
- [[#13167](https://github.com/redis/redis/pull/13167/)] Change FLUSHALL/FLUSHDB SYNC to run as blocking ASYNC
- [[#13178](https://github.com/redis/redis/pull/13178/)] kvstoreIteratorNext() wrongly reset iterator twice

### During April 27th
The following patches were applied:

- [[#13231](https://github.com/redis/redis/pull/13231/)] Fix forget to update the dict's node in the kvstore's rehashing list after defragment
- [[#13233](https://github.com/redis/redis/pull/13233/)] Fix CI failure caused by PR

### During May 6th
The following patches were applied:

- [[13251](https://github.com/redis/redis/pull/13251)] XREADGROUP from PEL should not affect server.dirty
