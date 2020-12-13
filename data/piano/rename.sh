for i in *.wav;
do
    mv $i ${i:(-7)}
done
