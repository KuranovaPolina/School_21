#!/bin/bash

function collectData {
    total_number_of_folders=$(find $1 -type d | wc -l);
    echo "Total number of folders (including all nested ones) = ${total_number_of_folders}";

    echo "TOP 5 folders of maximum size arranged in descending order (path and size):";
    du -ah $1 | sort -n -r | head -n 5 | awk 'BEGIN{i=1}{printf "%d - %s, %s\n", i, $2, $1; i++}'

    total_number_of_files=$(find $1 -type f | wc -l);
    echo "Total number of folders (including all nested ones) = ${total_number_of_files}";

    total_number_of_config_files=$(find $1 -type f -name *.conf| wc -l);
    total_number_of_text_files=$(find $1 -type f -name *.txt| wc -l);
    total_number_of_exe_files=$(find $1 -type f -perm /a=x | wc -l);

    arch="-name *.7z -o -name *.cab -o -name *.cbr -o -name *.deb -o -name *.exe -o -name *.gz -o -name *.gzip -o -name *.jar -o -name *.rar -o -name *.rpm -o -name *.sitx -o -name *.tar -o -name *.tar-gz -o -name *.zip -o -name *.zipx";

    total_number_of_log_files=$(find $1 -type f -name *.log| wc -l);
    total_number_of_arch_files=$(find $1 -type f ${arch}| wc -l);
    total_number_of_links_files=$(find $1 -type l| wc -l);
    echo "Number of:";
    echo "Configuration files (with the .conf extension) = ${total_number_of_config_files}";
    echo "Text files = ${total_number_of_text_files}";
    echo "Executable files = ${total_number_of_exe_files}";
    echo "Log files (with the extension .log) = ${total_number_of_log_files}";
    echo "Archive files = ${total_number_of_arch_files}";
    echo "Symbolic links = ${total_number_of_links_files}";

    echo "TOP 10 files of maximum size arranged in descending order (path, size and type):";
    i=1;
    IFS=$'\n';
    for file in $(find $1 -type f | xargs -r -d '\n' du -h | sort -rh | head -10)
    do
        file_name=$(echo $file | awk '{printf $2}');
        file_size=$(echo $file | awk '{printf $1}');
        file_ext=${file_name##*.}
        echo "$i - $file_name, $file_size, $file_ext";
        i=$(( $i + 1 ));
    done;

    echo "TOP 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file):";
    i=1;
    IFS=$'\n';
    for file in $(find $1 -type f -perm /a=x | xargs -r -d '\n' du -h | sort -rh | head -10)
    do
        file_name=$(echo $file | awk '{printf $2}');
        file_size=$(echo $file | awk '{printf $1}');
        file_hash=$(md5sum ${file_name} | awk '{printf $1}');
        echo "$i - $file_name, $file_size, $file_hash";
        i=$(( $i + 1 ));
    done;
}

function makeNormalFileName {
    if [[ $1 != "/" ]]; then
        echo ${1%?};
    else
        echo $1;
    fi;
}
