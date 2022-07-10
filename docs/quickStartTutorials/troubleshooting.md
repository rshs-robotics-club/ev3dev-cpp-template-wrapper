---
layout: default
title: "troubleshooting: common problems"
nav_order: 2
tag: "troubleshooting"
---

# trouble shooting
#### This section contains common problems and their solutions. If you can't find the solution to your problem, ask in [issues](https://github.com/rshs-robotics-club/ev3dev-cpp-template-wrapper/issues/)

---
### `No such container EV3PROGRAM found`.

Solution:
ensure that you have run `./scripts/dockersetup.sh`. This should set up the EV3PROGRAM container.

Solution 2:
Double check that the `compile.sh` file has CRLF line endings, and the `post_build.sh` and `runWithinContainer.sh` both have LF line endings. `compile.sh` is run in windows so it requires CRLF line endings, however the other 2 are run inside a linux environment, which required LF line endings.

---

### `Error response from daemon: You cannot remove a running container. Stop the container before attempting removal or force remove`

The likely cause of this error is that you closed the git bash popup window before the docker container was finished, or you just somehow managed to stop the bash script within the container

Solution:
Wait for ~30 seconds and retry running `compile.sh` the container should stop on its own
Solution 2:
Open up docker desktop and go to the `Containers / Apps` menu. Find the EV3PROGRAM container and click on the `Stop` button.

---

### `No such image <image name here>`
solution:
Ensure that you have already run `./scripts/dockersetup.sh`

---

### I can't run the `.sh` files pls help
solution:
make sure you have Git Bash installed (windows)
We currently have no support for MacOS yet, so we don't know if it is installed by default on MacOS.

---