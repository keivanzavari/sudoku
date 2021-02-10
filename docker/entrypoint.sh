#!/usr/bin/env bash

log() {
  local params="$@"
  echo $(date -u) $params >>/root/entrypoint.log
}

log_and_exec() {
  local params="$@"
  log "started:" $params
  $params
  log "... done"
}

log "Running entrypoint script"

log_and_exec "/etc/init.d/dbus start"
log_and_exec "/etc/init.d/avahi-daemon start"

USERNAME=${LOGNAME}
# Get current (original) UID of sv user
ORIGINAL_USERID=$(id -u ${USERNAME})
ORIGINAL_GROUPID=$(id -g ${USERNAME})

# Change uid, gid and assign ownership to user sv so that its UID matches the UID specified in USERID
log_and_exec "usermod -u ${USERID} ${USERNAME}"

log_and_exec "groupmod -g ${GROUPID} ${USERNAME}"

log_and_exec "chown --from :${ORIGINAL_GROUPID} -R :${GROUPID} /home/${USERNAME}"

log_and_exec "chown --from ${ORIGINAL_USERID} -R ${USERID} /home/${USERNAME}"

log_and_exec "chown -R ${USERID}:${GROUPID} /sv_data_files"

log_and_exec "chown -R ${USERID}:${GROUPID} /openpose/models"

log_and_exec "sysctl fs.inotify.max_user_watches=524288"

log "done"

bash -c "/bin/bash"
