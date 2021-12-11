CONTAINER_NAME="EV3PROGRAM"
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
SRC_DIR=${SCRIPT_DIR}/../
winpty docker rm ${CONTAINER_NAME}
winpty docker run -it --entrypoint /${SRC_DIR}/scripts/runWithinContainer.sh --name ${CONTAINER_NAME} -v /${SRC_DIR}:/${SRC_DIR} -w /${SRC_DIR} ev3cc
$SHELL