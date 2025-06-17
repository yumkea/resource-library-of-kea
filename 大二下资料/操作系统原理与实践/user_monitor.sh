#
# This program monitor user login in
#
if [ $# -eq 1 ]
then
  user=$(who)
  echo "Current user list is:"
  echo $user
  name=`who|grep $1`
  while [ -z "$name" ]
  do
    echo "waiting user [$1] …"
    sleep 5
    name=`who|grep $1`
  done

  echo "user [$1] is log on."
  exit
else
  echo "Usage: usr_monitor  username"
fi
