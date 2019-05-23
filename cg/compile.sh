#  chmod +x test.sh !
echo "compliling file : " $1
g++ $1 -o .OpenGlApp.out -lglut -lGLU -lGL
./.OpenGlApp.out