#include <iostream>
using namespace std;
#include "Image_Class.h"


string input(string ms) // function that takes input from user so that i can use it inside function's argument like this: [funcName(input("write here what will appear to the user"))]
{
    string d;
    cout << ms;
    getline(cin >> ws, d); 
    return d;
}

string isValidChoice6(string Msg){ // function to ensure user only enterd 1 or 2 or 3 or 4 or 5 or 6
    while (true)
    {
        if(Msg == "1" || Msg == "2" || Msg == "3" || Msg == "4" || Msg == "5" || Msg == "6")
            return Msg;
        else{
            cout << "Please choose a valid choice: ";
            getline(cin >> ws, Msg); // enter the message again
        }
    }
    
}

string isValidChoice3(string Msg){ // function to ensure user only enterd 1 or 2 or 3
    while (true)
    {
        if(Msg == "1" || Msg == "2" || Msg == "3")
            return Msg;
        else{
            cout << "Please choose a valid choice: ";
            getline(cin >> ws, Msg); // enter the message again
        }
    }
    
}

string isValidChoice4(string Msg){ // function to ensure user only enterd 1 or 2 or 3 or 4
    while (true)
    {
        if(Msg == "1" || Msg == "2" || Msg == "3" || Msg == "4")
            return Msg;
        else{
            cout << "Please choose a valid choice: ";
            getline(cin >> ws, Msg); // enter the message again
        }
    }
    
}

string isValidChoice(string Msg){ // function to ensure user enterd only 1 or 2
    while (true)
    {
        if(Msg == "1" || Msg == "2")
            return Msg;
        else{
            cout << "Please choose a valid choice: ";
            getline(cin >> ws, Msg); // enter the message again
        }
    }
    
}

void save_Image(Image& img, string&filename){
    // display a menu to the user until he saves with a valid name
    cout << "\n\nChoose How You Want to Save"<< endl;
    cout << "1- Save Image in Same Image File\n2- Save Image in New File\n3- End\n";
    string choice;
    choice = isValidChoice3(input("Please choose a number from the menu: "));

    if (choice == "1"){// Save Image in Same File
        img.saveImage(filename);
    }
    else if (choice == "2"){ // Save Image in New File
        cout << "Enter image name to store new image: ";
        getline(cin >> ws, filename);
        while (true){ // same while loop as the one at the begining of the function but this one is for making sure user enterd a name with correct extension
            try {
                    img.saveImage(filename);  // this line will stop the program if the user enterd a wrong file name extension
                    break;
            }
            catch(invalid_argument) {
                    cout <<  "\nEnter file Name with correct extension: ";
                    getline(cin >> ws, filename);
            }
        }
    cout << "\n";
        }
    else if (choice == "3"){ // if he chose End
        cout << "Thank You For Using Our Program";
        exit(0);
            }
}

void load_Image(Image& img, string&filename){
    //display a menu to the user until he enter a valid filename
    while (true){ // a loop that will stop when user enter correct file name
        Image img; // here it is in the scope of the the loop only not outside it

        try{
            img.loadNewImage(filename);  // this line will stop the program if the user enterd a wrong file name
            break; // it will reach break only if the image is loaded succefuly 
        }
        catch(invalid_argument){ // invalid argument is the class that is thrown from this exception [in the library inside the loadNewImage function you will find throw std::invalid_argument]
            cout <<  "\nEnter file Name: ";
            getline(cin >> ws, filename);
        }
    }
}

void loadWithaCurrentImage(Image& img, string&filename){
    cout << "\nWhat Do You Want To Do With The Current Image?" << endl;
    cout << "1- Save It And Then Load Another Image\n2- Discard Current And then Load Another Image\n3- End\n";
    string choice;
    choice = isValidChoice3(input("Please choose a number from the menu: "));

    if (choice == "1"){// Save Then load
        save_Image(img, filename);
    }

    // else if (choice == "2"){ // Discard then load
        //in this choice we dont need to do anything i will just break from the inner while(true) loop in the mainMenu function so it starts the bigger while(true) loop which contain the loading image menu
    //     }
    else if (choice == "3"){ // if he chose End
        cout << "Thank You For Using Our Program";
        exit(0);
    }
}

void darkenAndLighten(Image& img){
    string choice;
    cout << "\n1- Lighten by 50%\n2- Darken by 50%\n"; // displayed to te user
    choice = isValidChoice(input("Please choose a number from the menu: "));// make sure he enterd 1 or 2
    if(choice == "2"){
        for (int i = 0; i < img.width; i++){
            for(int j = 0; j < img.height; j++){
                for(int k = 0; k < 3; k++){ 
                        img(i, j, k) /= 2; // divide each color value by 2 so it darkens by 50%, [Note: it will not reach a negative number or exceed 255], this process which is [/2], is the same as multiplying each color value by -0.5 [-50%] and then add it to the original color value mathematically  

                }
            }
        }
    }
    if(choice == "1"){
        for (int i = 0; i < img.width; i++){
            for(int j = 0; j < img.height; j++){
                for(int k = 0; k < 3; k++){
                    if(img(i, j, k) * 1.5 > 255 ) // if color exceeds 255
                        img(i, j, k) = 255; // set it to a static value of 255(uncahangeable)
                    else // if it doesn't exceed 255 do the multiplication
                        img(i, j, k) *= 1.5; // multiply each color value by 1.5 so it lightens by 50%, this process which is [*1.5], is the same as multiplying each color value by 0.5 or [50%] and then add it to the original color value mathematically  
                }
            }
        }
    }
}

void grayScale(Image&luffy){
    for (int i = 0; i < luffy.width; i++)
    {
        for (int j = 0; j < luffy.height; j++)
        {
            int avg = 0;
            for (int k = 0; k < 3; k++)
            {
                avg += luffy(i, j, k);
            }
            avg = avg/3;

            luffy(i, j, 0) = avg;
            luffy(i, j, 1) = avg;
            luffy(i, j, 2) = avg;
        }
    }
}

void inverted(Image&image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
}

void blackAndWhite(Image&image){
    // a constant to compare with each pixel
    const int borderline = 127; 

    // Loop through each pixel of the image
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            // Calculate the average intensity across all color channels
            for (int k = 0; k < 3; k++) {
                avg += image(i, j, k);
            }
            avg /= 3; // Calculate the average

            int newvalue;
            // Determine if the pixel should be black or white based on the borderline value
            if (avg < borderline) {
                newvalue = 0; // Set pixel to black
            }
            else {
                newvalue = 255; // Set pixel to white
            }

            // Set all color channels of the pixel to the determined value
            image(i, j, 0) = newvalue;
            image(i, j, 1) = newvalue;
            image(i, j, 2) = newvalue;
        }
    }
}

//===================================================
// Filter 5 [Flip Image]
//===================================================
void vertically(Image&image){
    // Flip vertically
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height / 2; ++j) {
            for (int k = 0; k < 3; ++k) {
                // Swap pixels vertically
                std::swap(image(i, j, k), image(i, image.height - 1 - j, k));
            }
        }
    }
}
void horizontally(Image & image){
    // Flip horizontally
    for (int i = 0; i < image.width / 2; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                // Swap pixels horizontally
                std::swap(image(i, j, k), image(image.width - 1 - i, j, k));
            }
        }
    }
}
void flipImage(Image&image){
    cout << "\nChoose the position you want to flip \n1- vertically \n2- horizontally\n";
    string position;
    position = isValidChoice(input("Please choose a number from the menu: "));

    if (position == "1")
    {
        vertically(image);
    }
    if (position == "2")
    {
        horizontally(image);
    }

    



}
//===================================================
void mainMenu(){
    cout << "------Welcome to Image Processing Program------" << endl;
    
    while(true){
        cout << "Choose What you want to do"<< endl;
        cout << "1 -Load a new Image\n2- End\n"<< endl;
        string choice = isValidChoice(input("Please choose a number from the menu: "));
//=============================== 
        if (choice == "1"){ // if user chose load an image
            string filename; 
            cout << "Enter image's Name: ";
            getline(cin >> ws, filename);
            Image img; //i declared it here to be defined in the whole function  
            load_Image(img, filename);// a function i created to ensure user entered a valid filename
            
            img.loadNewImage(filename); // the built-in load function
    while(true){ // loop that works until the user choose (End)
            cout << "\n\nChoose What you want to do"<< endl;
            cout << "1 -Apply a Fliter\n2- Save Current Image\n3- Load an Image\n4- End\n";
            choice = isValidChoice4(input("Please choose a number from the menu: "));
//===============================                   
            if(choice == "1"){ // if he chose apply a filter

                cout << "\n\nChoose Which Filter to Apply"<< endl;
                cout << "1- Gray Scale Filter\n2- Darken And Lighten Filter\n3- Invert Filter\n4- Black And White Filter\n5- Flip Image\n6- End\n";
                choice = isValidChoice6(input("Please choose a number from the menu: "));
//=============================== 
                if (choice == "1"){ // Gray Scale Filter
                    grayScale(img);
                }else if (choice == "2"){ // Darken And Lighten Filter
                    darkenAndLighten(img);
                }else if (choice == "3"){ // Invert Filter
                    inverted(img);
                }else if (choice == "4"){ //Black And White Filter
                    blackAndWhite(img);
                }else if (choice == "5"){ // Flip Image Filter
                    flipImage(img);
                }else if (choice == "6"){ // End
                    cout << "Thank You For Using Our Program";
                    exit(0); // exit from program
                }

            }
            else if (choice == "2") { // if he chose Save current Image
                save_Image(img, filename);// saves the image
            }
            else if (choice == "3"){ // Load another image
                loadWithaCurrentImage(img, filename); // calls this function
                break;// this break will take him to the outer while loop to start the loading Image menu and then return back to the inner while loop again
            }
            else if (choice == "4"){ // if he chose End
                cout << "Thank You For Using Our Program";
                exit(0); // exit from program
            }
        }
//==========================================================================
    }
    else if (choice == "2"){ // if he chose End
                cout << "Thank You For Using Our Program";
                exit(0); // exit from program
            }
    }
}

int main(){
mainMenu();
return 0;
}



    