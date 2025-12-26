./collect_answers.sh
./collect_cli.sh
./collect_scripts.sh
./collect_so.sh
cp ./setup_py310_venv.sh submission/
./readme_to_index.sh README.md submission/index.html
rm -f submission.tar
tar -cf submission.tar submission/