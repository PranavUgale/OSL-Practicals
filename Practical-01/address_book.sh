#!/bin/bash

FILE="addressbook.txt"

while true
do
    echo
    echo "----- ADDRESS BOOK -----"
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Insert Record"
    echo "4. Delete Record"
    echo "5. Modify Record"
    echo "6. Exit"

    read -p "Enter your choice: " ch

    case $ch in
        1)
            > "$FILE"
            echo "Address Book Created."
            ;;

        2)
            if [ -f "$FILE" ]; then
                cat "$FILE"
            else
                echo "Address Book does not exist."
            fi
            ;;

        3)
            touch "$FILE"
            read -p "Enter Name: " name
            read -p "Enter Phone: " phone
            echo "$name $phone" >> "$FILE"
            echo "Record Inserted."
            ;;

        4)
            if [ -f "$FILE" ]; then
                read -p "Enter Name to Delete: " name

                if grep -Fq "$name " "$FILE"; then
                    grep -Fv "$name " "$FILE" > temp.txt
                    mv temp.txt "$FILE"
                    echo "Record Deleted."
                else
                    echo "Record Not Found."
                fi
            else
                echo "Address Book does not exist."
            fi
            ;;

        5)
            if [ -f "$FILE" ]; then
                read -p "Enter Name to Modify: " name

                if grep -Fq "$name " "$FILE"; then
                    grep -Fv "$name " "$FILE" > temp.txt
                    mv temp.txt "$FILE"

                    read -p "Enter New Name: " newname
                    read -p "Enter New Phone: " phone

                    echo "$newname $phone" >> "$FILE"
                    echo "Record Modified."
                else
                    echo "Record Not Found."
                fi
            else
                echo "Address Book does not exist."
            fi
            ;;

        6)
            echo "Exiting..."
            exit 0
            ;;

        *)
            echo "Invalid Choice."
            ;;
    esac
done