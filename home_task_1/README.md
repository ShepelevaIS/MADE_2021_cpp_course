
Вариант #43
Создать структуру для хранения информации о заинтересованных сторонах проекта: их роли (заказчик, покупатель, разработчик и пр.), наименовании или имени, степени влияния и т.д. Составить с ее использованием программу вывода информации обо всех заинтересованных лицах, наиболее соответствующих заданным пользователем критериям.

lcov -t "tests/test_specialists" -o coverage.info -c -d specialists_db_lib/ 

genhtml -o report coverage.info

cd build/report

python3 -m http.server 8000

./linters/run.sh
clang-format -i main.c
valgrind --tool=memcheck --leak-check=yes ./specialists_db_lib/specialists_db
gcc -fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error ./specialists_db
