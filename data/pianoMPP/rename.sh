for i in *.mp3;
do
    ffmpeg -i $i ${i::-7}wav
done
