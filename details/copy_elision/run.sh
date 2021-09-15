echo "copy-elide version"

g++ copy_elision.cc -o elision.out
./elision.out

echo "no copy-elide version"

g++ copy_elision.cc -o noelision.out -fno-elide-constructors
./noelision.out