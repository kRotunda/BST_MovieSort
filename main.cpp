#include <iostream>
#include <fstream> // for file IO
#include <typeinfo> // for typeid
#include <sstream> // for splitting strings
#include "bst.h" // our file for bst
using namespace std;


/*
* Main function (driver)
* take care of reading in the file and creating linkedList
*/

int main()
{
	// get movies from the file, one at a time
	string inputFile = "movies.txt";
	ifstream f(inputFile);
	bst* tree = new bst();
	if (!f.is_open())
	{
		cout << "Could not open file!" << endl;
	}
	else
	{
		string inputLine;
		while (getline(f, inputLine, '\n'))
		{
			stringstream ss(inputLine);
			string title, rating_s, year_s;
			getline(ss, title, ',');
			getline(ss, rating_s, ',');
			getline(ss, year_s, ',');
			tree->addMovie(title, stoi(rating_s), stoi(year_s));
		}
	}

	// write a loop to keep taking user choices
	bool ok = true;
	while (ok)
	{
		// prompt user for choice
		string choice;
		cout << "Enter a choice:\nAdd a movie (1)\nDelete a movie (2)\nFind a movie (3)\nPrint with Rating (4)\nQuit (5)" << endl;
		getline(cin, choice);
		cout << "You entered: " << choice << endl;
		// handle case 1: add a movie
		if (choice == "1")
		{
			string title, rating_s, year_s;
			cout << "Enter the title of the new movie: " << endl;
			getline(cin, title, '\n');
			cout << "Enter rating of the new movie: " << endl;
			getline(cin, rating_s, '\n');
			cout << "Enter the release year of the new movie: " << endl;
			getline(cin, year_s, '\n');
			tree->addMovie(title, stoi(rating_s), stoi(year_s));
		}
		// handle case 2: delete a movie
		else if (choice == "2")
		{
			string title;
			cout << "Enter the title of the movie you want to delete: " << endl;
			getline(cin, title, '\n');
			tree->deleteMovie(title);
		}
		// handle case 3: find a movie
		else if (choice == "3")
		{
			string title;
			cout << "Enter the title of the movie you want to find: " << endl;
			getline(cin, title, '\n');
			tree->findMovie(title);
		}
		// handle case 4: print with rating
		else if (choice == "4")
		{
			string rating;
			cout << "Enter the cut-off rating for printing: " << endl;
			getline(cin, rating, '\n');
			tree->printMoviesRating(stoi(rating));
		}
		// handle case 5: exit
		else if (choice == "5")
		{
			cout << "EXITING" << endl;
			ok = false;
		}
		// handle invalid input by exiting
		else
		{
			cout << "Invalid choice, exiting!" << endl;
			ok = false;
		}
	}

	// print out the BST before exiting
	cout << "====Printed BST====" << endl;
	tree->printMovies();
	delete tree;

	return 0; //return "success" status
}
