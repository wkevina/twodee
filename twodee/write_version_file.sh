PROJ_DIR=$1
DEST=$2

file=build_version.txt

cd $PROJ_DIR

COMMIT=$(git show --quiet --format="%H")
DATE=$(git show --quiet --format="%cI")

cd $DEST

touch $file

echo git-commit:$COMMIT > $file
echo date:$(date) >> $file
