//
//  main.cpp
//  HW6
//
//  Created by Spencer Christensen on 4/24/16.
//  Copyright © 2016 Spencer Christensen. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdio>


using namespace std;

int hashbrowns(int);

bool quadratic_probe(int key, int hash_table[], int i) {
    //key-- the position where it's supposed to hash too.
    //i -- user entered at the beggining
    
    int max = 65000;
    int pos;
    pos = hashbrowns(key);
    for(i= ((pos+(i*i)) % max); i > 0 && (hash_table[i] != 0); i++){
        if (hash_table[i] == 0) {
            hash_table[i] = key;
            return true;
        }
    }
    return false;
}

//Hashes a given nine digit number.
int hashbrowns(int key) {
    //given a number, get digits 3,5,7, and 8
    int eight;
    int seven;
    int five;
    int three;
    
    eight = (key / 10) % 10;
    seven = (key / 100) % 10;
    five = (key / 10000) % 10;
    three = (key / 1000000) % 10;
    
    char * e = new char[1];
    char * s = new char[1];
    char * f = new char[1];
    char * t = new char[1];

    sprintf(e, "%i", eight);
    sprintf(s, "%i", seven);
    sprintf(f, "%i", five);
    sprintf(t, "%i", three);
    
    char * myString = strcat(strcat(t, f), strcat(s, e));
    
    int x = atoi(myString);
    
    return x;
}

//Reads file in
bool read_file(string file_name,int w[])
{
    int i = 0;
    //char comma = ',';
    ifstream in;
    in.open(file_name);
    if(!in.is_open()) {
        cout << "Cannot find file" << endl;
        return false;
    }
    char * word = new char [100];
    int s_word;
    while(in.peek()!=EOF)
    {
        in.getline(word,100,',');
        s_word=atoi(word);
        w[i] = s_word;
        i++;
    }
    in.clear();
    in.close();
    return true;
}

//Write out elements of the array to file
bool write_to_file (string file_name, int array[]) {
    ofstream out;
    out.open(file_name);
    for (int i = 0; i < 64998; i++) {
        out << array[i] << ", ";
    }
    out << array[65000];
    out.clear();
    out.close();
    return true;
}

 int main(int argc, const char * argv[]) {
    //Before hashing, ask user for number between 1 and 450 million. This is for quadratic probing.
    //When collision occurs, use quadratic probing without replacement
    //When fully hashed, write out the hash table to file, comma delimited.
     
    int a[65000];
    int index;
    int M;
    int hash_table[65000];
    
    cout << "Enter a number between 1 and 450,000,000: " << endl;
    cin >> M;
    read_file("/Users/Spencer/Desktop/er.txt", a);
     
     
    //Loop to fill array with values.
    for (int i = 0; i < 65000; i++) {
        index = hashbrowns(a[i]);
        if (hash_table[index] == 0){
            hash_table[index] = a[i];
        }
        
        //If the position where the element should be placed is taken, call the quadratic probing method
        else {
            quadratic_probe(a[i], hash_table, M);
        }
    }
     
     write_to_file("/Users/Spencer/Desktop/hashed_socials.txt", hash_table);
  
 }



//"/Users/Spencer/Desktop/everybodys_social.txt"
