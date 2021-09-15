$ array=($(ls gamedata/textures/))
for i in "${array[@]}"
do
	git add gamedata/textures/$i
	git commit -m "gamedata/textures/${i}"
	git push origin main
done