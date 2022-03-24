#ifndef BST_H_
#define BST_H_
#include <iostream>
using namespace std;

// must use this struct
struct movie
{
	string title;
	int rating;
	int year;
	movie* parent;
	movie* leftChild;
	movie* rightChild;
};

class bst {
private:
	movie* root;
	void destroy(movie* node); // helper function for destructor
public:
	bst(); //constructor
	~bst(); //destructor
	movie* search(string title); // returns the node with the matching title
	void addMovie(string name, int rating, int year); //method for inserting a new movie
	void deleteMovie(string title); //method for removing a movie
	movie* findMin(movie* node); //helper function for deleteMovie
	void findMovie(string title); // method for finding and printing out the information about a movie
	void printMoviesRating(int rating); // helper function
	void printMoviesRating(movie* node, int rating); // method to print all movies in order with rating above a certain value
	void printMovies(); // helper function
	void printMovies(movie* node); // method (already implemented) that will print the movies in order
};

// Constructor
bst::bst() {
	root = nullptr;
}

/*
* Method name: destroy
* Purpose: helper method for the destructor
* @param node - the current node
* @return none
* Note: recursively destroy nodes, doing a post-order traversal
*/
void bst::destroy(movie* node)
{
	if (node == nullptr) {
		delete node;
	}
	else {
		if (node->leftChild != nullptr) {
			destroy(node->leftChild);
		}
		if (node->rightChild != nullptr) {
			destroy(node->rightChild);
		}
		else {
			delete node;
		}
	}
}

// Destructor
// use a post-order traversal to delete movies one at a time by
// calling destory with root
bst::~bst() {
	destroy(root);
}


/*
* Method name: search
* Purpose: accepts a title searches the tree for the title
* @param title - the title of the movie
* @return - pointer to the movie node with the title
* Note: Use the iterative approach (not recursive) so we don't
* 	have to send another node parameter.
* 	You can call this from various other methods!
*/
movie* bst::search(string title)
{
	movie* temp = root;
	while (temp->title != title) {
		if (temp->title > title) {
			temp = temp->leftChild;
		}
		if (temp->title < title) {
			temp = temp->rightChild;
		}
		if (temp->title == title) {
			return temp;
		}
	}
}

/*
* Method name: addMovie
* Purpose: accepts a title and creates a new movie node, puts it in the BST
* @param title - the title of the movie
* @param rating - the integer rating of the movie
* @param year - the integer year that the movie came out
* @return - none
* Note: Create a new movie node with the specified parameters.
* 	then go through the tree to put it in the lexicographically correct
* 	spot in the tree.
*/
void bst::addMovie(string title, int rating, int year)
{	
	movie* temp = new movie;
	temp->title = title;
	temp->rating = rating;
	temp->year = year;
	temp->parent = nullptr;
	temp->leftChild = nullptr;
	temp->rightChild = nullptr;
	if (root == nullptr) {
		root = temp;
	}
	else {
		movie* runner = root;
		while (runner != nullptr) {
			if (runner->title > temp->title || runner->title == temp->title) {
				if (runner->leftChild == nullptr) {
					break;
				}
				runner = runner->leftChild;
			}
			if (runner->title < temp->title) {
				if (runner->rightChild == nullptr) {
					break;
				}
				runner = runner->rightChild;
			}
		}
		temp->parent = runner;
		if (temp->title > runner->title || temp->title == runner->title) {
			runner->rightChild = temp;
			temp->parent = runner;
		}
		if (temp->title < runner->title) {
			runner->leftChild = temp;
			temp->parent = runner;
		}
	}
}


/*
* Method name: findMin
* Purpose: accepts a node that you want to start your search at and returns the minimum
* 	value node in that subtree
* @param node - the start node
* @return - the node with the smallest title in the subtree starting at node
* Note: this is a helper function for deleteMovie!
*/
movie* bst::findMin(movie* node)
{
	movie* runner = root;
	while (runner != node) {
		if (runner->title > node->title) {
			runner = runner->leftChild;
		}
		if (runner->title < node->title) {
			runner = runner->rightChild;
		}
	}
	movie* runnerTwo = runner;
	while (runnerTwo != nullptr) {
		runnerTwo = runnerTwo->leftChild;
	}
	return runnerTwo->parent;
}

/*
* Method name: deleteMovie
* Purpose: accepts a title and removes
* @param title - the title of the movie to be removed 
* @return - none
* Note: find the movie with the title matching the input and
* 	remove it from the tree, remember, you may have to move things
* 	around to maintain the BST properties! You must follow the
* 	pseudocode on pages 178, 179, and 180 in the textbook
*/
void bst::deleteMovie(string title)
{
	movie* runner = root;
	while (runner->title != title) {
		if (runner->title > title) {
			runner = runner->leftChild;
		}
		if (runner->title < title) {
			runner = runner->rightChild;
		}
		if (runner == nullptr) {
			break;
		}
	}
	//movie not found
	if (runner == nullptr) {
		cout << "Movie title couldn't be found!" << endl;
	}
	//is Root
	if (runner == root) {
		if (runner->leftChild == nullptr && runner->rightChild == nullptr) { //ROOT no children
			delete runner;
			bst();
		}
		else if (runner->leftChild != nullptr && runner->rightChild == nullptr) { //ROOT one child: has left child
			runner->leftChild->parent = nullptr;
			root = runner->leftChild;
			delete runner;
		}
		else if (runner->leftChild == nullptr && runner->rightChild != nullptr) { //ROOT one child: has right child
			runner->rightChild->parent = nullptr;
			root = runner->rightChild;
			delete runner;
		}
		else if (runner->leftChild != nullptr && runner->rightChild != nullptr) { //ROOT has two children
			movie* temp = runner->leftChild;
			temp = runner->leftChild;
			runner->rightChild->parent = nullptr;
			root = runner->rightChild;
			delete runner;
			runner = root;
			while (runner->leftChild != nullptr) {
				runner = runner->leftChild;
			}
			temp->parent = runner;
			runner->leftChild = temp;
		}
	}
	//had no children
	else if (runner->leftChild == nullptr && runner->rightChild == nullptr) {
		if (runner->parent->title > runner->title) { //left child
			runner->parent->leftChild = nullptr;
			runner->parent = nullptr;
			delete runner;
		}
		else if (runner->parent->title < runner->title || runner->parent->title == runner->title) { //right child
			runner->parent->rightChild = nullptr;
			runner->parent = nullptr;
			delete runner;
		}
	}
	//had one child
	else if (runner->leftChild != nullptr && runner->rightChild == nullptr ) { //has left child
		if (runner->parent->title > runner->title) { //left child
			runner->parent->leftChild = runner->leftChild;
			runner->leftChild->parent = runner->parent;
			delete runner;
		}
		else if (runner->parent->title < runner->title || runner->parent->title == runner->title) { //right child
			runner->parent->rightChild = runner->leftChild;
			runner->leftChild->parent = runner->parent;
			delete runner;
		}
	}
	else if (runner->leftChild == nullptr && runner->rightChild != nullptr) { //has right child
			if (runner->parent->title > runner->title) { //left child
				runner->parent->leftChild = runner->rightChild;
				runner->rightChild->parent = runner->parent;
				delete runner;
			}
			else if (runner->parent->title < runner->title || runner->parent->title == runner->title) { //right child
				runner->parent->rightChild = runner->rightChild;
				runner->rightChild->parent = runner->parent;
				delete runner;
			}
	}
	//has two children
	else if (runner->leftChild != nullptr && runner->rightChild != nullptr) {
		movie* temp = runner->leftChild;
		if (runner->parent->title > runner->title) { //left child
			runner->parent->leftChild = runner->rightChild;
			runner->rightChild->parent = runner->parent;
			runner = runner->rightChild;
		}
		else if (runner->parent->title < runner->title || runner->parent->title == runner->title) { //right child
			runner->parent->rightChild = runner->rightChild;
			runner->rightChild->parent = runner->parent;
			runner = runner->rightChild;
		}
		while (runner->leftChild != nullptr) {
			runner = runner->leftChild;
		}
		temp->parent = runner;
		runner->leftChild = temp;
	}
}

/*
* Method name: findMovie
* @param title - the title of the movie
* @return - none
* Note: find the movie and print out the associated information. Hint,
* 		if you implement search first, this method is very easy!
*/
void bst::findMovie(string title)
{
	movie* temp = search(title);
	cout << "Movie Title: " << temp->title << " Rating: " << temp->rating << " Year: " << temp->year << endl;

}

// helper function to call printMoviesRating with root
void bst::printMoviesRating(int rating)
{
	if (root->rating >= rating) {
		cout << "Movie Title: " << root->title << " Rating: " << root->rating << " Year: " << root->year << endl;
	}
	if (root->leftChild != nullptr) {
		printMoviesRating(root->leftChild, rating);
	}
	if (root->rightChild != nullptr) {
		printMoviesRating(root->rightChild, rating);
	}
}


/*
* Method name: printBST
* Purpose: prints each movie's information, in-order traversal!
* @param node - the node to start at
* @param rating - the cut off rating, for example, rating = 3 then you should
					only print movies with a rating of 3 or higher
* @return - none
*/
void bst::printMoviesRating(movie* node, int rating)
{
	if (node->rating >= rating) {
		cout << "Movie Title: " << node->title << " Rating: " << node->rating << " Year: " << node->year << endl;
	}
	if (node->leftChild != nullptr) {
		printMoviesRating(node->leftChild, rating);
	}
	if (node->rightChild != nullptr) {
		printMoviesRating(node->rightChild, rating);
	}
}


// helper function to call printMovies with root
void bst::printMovies()
{
	printMovies(root);
}

/*
* Method name: printBST
* Purpose: prints each movie's information, in-order traversal!
* @return - none
*/
void bst::printMovies(movie* node)
{
	if(node!=NULL)
	{
		printMovies(node->leftChild);
		cout << "Title: " << node->title << ", Rating: " << node->rating << ", Year: " << node->year << endl;
		printMovies(node->rightChild);
	}
}
#endif