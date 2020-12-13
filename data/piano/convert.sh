for i in *.ogg;
do
    ffmpeg -i $i ${i::-3}wav
    echo "$i"
done
