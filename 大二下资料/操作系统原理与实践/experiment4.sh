#
# Monitor for file status
#
clear
test_count=0
change_count=0
echo -n "Input file name:" 
read FILENAME
if [ -f "$FILENAME" ]; then
  FILESIZE=`ls -l ${FILENAME} | cut -d " " -f 5`
  echo "file size is $FILESIZE"
  echo "Current status of [$FILENAME] is:"
  echo `ls -l $FILENAME`
while (( $test_count<10 ))
do
echo "test file status ..."
TEMP=`ls -l ${FILENAME} | cut -d " " -f 5`
if [ $TEMP -ne $FILESIZE ]; then
echo "file [$FILENAME] size changed!"
FILESIZE="$TEMP"
test_count=0
change_count=$((change_count + 1)) 
if [ $change_count -eq 2 ];then 
echo "Change number exceed two,test end!"
exit 
fi
fi
test_count=$((test_count + 1)) 
sleep 5    
done  
echo "test number exceed ten!"
else
  echo "Can't find the file [$FILENAME]"
fi
