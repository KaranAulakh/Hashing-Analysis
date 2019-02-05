#include <iostream>
#include <cstdlib>
#include <math.h>

using namespace std;

/*
 * the hash_chaining class is used to create all the hash maps that will implement chaining resolution. The 
 * class uses an array of node pointers that can be added to in order to create a list. There is no explicit
 * head pointer beacuse the array in itself contains the head node to each list. The class also contains
 * data types to keep track of and calculate the the size, num of elements store, load factor and number
 * of collisions. The load factor is calculated in every addition to the hash map
 */

class hash_chaining
{
	struct node
	{
		int value;
		node* next;
	};
	
	private: 
		float num_stored;
		int size;
		float load_factor;
		int collisions;
		node* hash_map;
	public:
		hash_chaining(int given_size):size(given_size), collisions(0), load_factor(0), num_stored(0)
		{
			hash_map = new node[size];
			for (int i = 0; i < size; i++)
			{
				node* tmp = new node;
				tmp -> value = -1;
				tmp -> next = NULL;
				hash_map[i] = *tmp;
			}
		}
		float get_load_factor() { return load_factor; }
		int get_collisions() { return collisions; }
		void add(int given_key, int given_value)
		{
			num_stored++;
			load_factor = num_stored / size; 
			if (hash_map[given_key].value == -1)
				hash_map[given_key].value = given_value;
			else 
			{
				collisions++;
				node* tmp = new node;
				*tmp = hash_map[given_key];
				while (tmp->next)
				{
					tmp = tmp->next;
				}
				node* to_add = new node;
				to_add->value = given_value;
				tmp -> next = to_add; 
			}
		}
		/* 
		 * the folowing two methods could be implemented to actually use the hash map although not 
		 * required for the experiment, although if uncommented and used, the add method will have to
		 * tweaked back to consider the case a node already exists but is changed to a value of -1
		 * to symbolize a deleted node
		 */

		/* 
		node* search(int given_key, int given_value)
		{
			node* failed = new node;
			failed -> value = -3;
			if (hash_map[given_key]->value == -1)
				return failed;

			node* tmp = hash_map[given_key];
			do
			{
				if (tmp->value == given_value)
					return tmp; 

				tmp = tmp->next;
			}
			while (tmp);

			return failed;
		}

		bool remove(int given_key, int given_value)
		{
			node* to_delete = search(given_key, given_value);
			if (to_delete -> value == -3)
				return false;
			if (to_delete -> next == NULL)
			{
				to_delete -> value == -1;
				return true;
			}	
			else if ((to_delete -> next) -> value == -1)
			{
				to_delete -> value == -1;
				return true;
			}
			else
			{
				node* tmp = hash_map[given_key];
				// iterate until one node before the node to delete
				while ((tmp -> next) -> value != given_value)
				{
					tmp = tmp -> next;
				}
				tmp -> next = to_delete -> next;
				delete to_delete;
			}
		}
		*/
};

/*
 * the hash_open_addressing class is used to create all the hash maps that will implement open addressinsg 
 * resolution. The class uses an array to store the value as an integer. In order to add to the hash map
 * in the case the desired key is already taken. The class iterates from the desired key to the end of the 
 * array to find an open spot. If none is found it will reset to the front of the array and iterate until
 * the original key. It'll use the first open spot for the element to add. The class also contains
 * data types to keep track of and calculate the the size, num of elements store, load factor and number
 * of collisions. The load factor is calculated in every addition of to the hash map
 */

class hash_open_addressing
{
	private:
		float num_stored;
		int size;
		float load_factor;
		int collisions;
		int* hash_map;
	public:
		hash_open_addressing(int given_size):size(given_size), collisions(0), load_factor(0), num_stored(0) 
		{
			hash_map = new int[size];
			for (int i = 0; i < size; i++)
			{
				hash_map[i] = -1;
			}
		}
		float get_load_factor() { return load_factor; }
		int get_collisions() { return collisions; }
		void add(int given_key, int given_value)
		{
			num_stored++;
			load_factor = num_stored / size;
			if (hash_map[given_key] == -1)
				hash_map[given_key] = given_value;
			else
			{
				collisions++;
				for (int i = given_key; i < size; i++)
				{
					if (hash_map[i] == -1)
					{
						hash_map[i] = given_value;
						return;
					}
				}
				for (int i = 0; i < given_key; i++)
				{
					if (hash_map[i] == -1)
					{
						hash_map[i] = given_value;
						return;
					}
				}
				cout << "Error no more room in the table";
			}
		}
};

int key_mod (int random, int size)
{	
	return random % size;
}

int key_mid_square(int random, int size)
{
	int key = random * random;                           // key squared
	float log_key = (log(key) / log(2));                 // log of key squared
	float log_size = (log(size) / log(2));               // log of size
	int power_n = ceil((log_key - log_size) / 2);        // get rid of half of the unwanted bits
	key = floor(key / pow(2.0, power_n));                // get rid of the other half
	key = key % size;                                    // determine final key
	return key;
}

int generate_random_key(int table_size)
{
	return rand() % ((table_size * 3) + 1);
}

int main() 
{
	/*******************************************************************************/
	/*****  First Experiment, using key mod table size and chaining resolution *****/
	/*******************************************************************************/

	// table size 10
	cout << "\n\n\ncalculating results for key mod with chaining resolution with table size 10...";
	hash_chaining* mod_chaining_map_1 = new hash_chaining(10);
	while (mod_chaining_map_1->get_load_factor() < 1)
	{
		mod_chaining_map_1->add(key_mod(generate_random_key(10), 10),1);
		cout << "\nload factor is: " << mod_chaining_map_1->get_load_factor() << "  || collisions are: " << mod_chaining_map_1->get_collisions();
	}	
	
	// table size 25
	cout << "\n\n\ncalculating results for key mod with chaining resolution with table size 25...";
	hash_chaining* mod_chaining_map_2 = new hash_chaining(25);
	while (mod_chaining_map_2->get_load_factor() < 1)
	{
		mod_chaining_map_2->add(key_mod(generate_random_key(25), 25),1);
		cout << "\nload factor is: " << mod_chaining_map_2->get_load_factor() << "  || collisions are: " << mod_chaining_map_2->get_collisions();
	}

	// table size 100
	cout << "\n\n\nncalculating results for key mod with chaining resolution with table size 100...";
	hash_chaining* mod_chaining_map_3 = new hash_chaining(100);
	while (mod_chaining_map_3->get_load_factor() < 1)
	{
		mod_chaining_map_3->add(key_mod(generate_random_key(100), 100),1);
		cout << "\nload factor is: " << mod_chaining_map_3->get_load_factor() << "  || collisions are: " << mod_chaining_map_3->get_collisions();
	}	

	/*******************************************************************************/
	/****** Second experiment, using key mid square and chaining resolution ******* /
	/*******************************************************************************/

	// table size 10
	cout << "\n\n\ncalculating results for mid square with chaining resolution with table size 10...";
	hash_chaining* mid_square_chaining_map_1 = new hash_chaining(10);
	while (mid_square_chaining_map_1->get_load_factor() < 1)
	{
		mid_square_chaining_map_1->add(key_mod(generate_random_key(10), 10),1);
		cout << "\nload factor is: " << mid_square_chaining_map_1->get_load_factor() << "  || collisions are: " << mid_square_chaining_map_1->get_collisions();
	}	
	
	// table size 25
	cout << "\n\n\ncalculating results for mid square with chaining resolution with table size 25...";
	hash_chaining* mid_square_chaining_map_2 = new hash_chaining(25);
	while (mid_square_chaining_map_2->get_load_factor() < 1)
	{
		mid_square_chaining_map_2->add(key_mod(generate_random_key(25), 25),1);
		cout << "\nload factor is: " << mid_square_chaining_map_2->get_load_factor() << "  || collisions are: " << mid_square_chaining_map_2->get_collisions();
	}

	// table size 100
	cout << "\n\n\ncalculating results for mid square with chaining resolution with table size 100...";
	hash_chaining* mid_square_chaining_map_3 = new hash_chaining(100);
	while (mid_square_chaining_map_3->get_load_factor() < 1)
	{
		mid_square_chaining_map_3->add(key_mod(generate_random_key(100), 100),1);
		cout << "\nload factor is: " << mid_square_chaining_map_3->get_load_factor() << "  || collisions are: " << mid_square_chaining_map_3->get_collisions();
	}	

	/*******************************************************************************/
	/*** third experiment, with key mod table size and open addressing resolution **/
	/*******************************************************************************/

	// table size 10
	cout << "\n\n\ncalculating results for key mod with open addressing resolution with table size 10...";

	hash_open_addressing* mod_oa_map_1 = new hash_open_addressing(10);
	while (mod_oa_map_1->get_load_factor() < 1)
	{
		mod_oa_map_1->add(key_mod(generate_random_key(10), 10), 1);
		cout << "\nload factor is: " << mod_oa_map_1->get_load_factor() << "  || collisions are: " << mod_oa_map_1->get_collisions();
	}

	// table size 25
	cout << "\n\n\ncalculating results for key mod with open addressing resolution with table size 25...";

	hash_open_addressing* mod_oa_map_2 = new hash_open_addressing(25);
	while (mod_oa_map_2->get_load_factor() < 1)
	{
		mod_oa_map_2->add(key_mod(generate_random_key(25), 25), 1);
		cout << "\nload factor is: " << mod_oa_map_2->get_load_factor() << "  || collisions are: " << mod_oa_map_2->get_collisions();
	}

	// table size 100
	cout << "\n\n\ncalculating results for key mod with open addressing resolution with table size 100...";

	hash_open_addressing* mod_oa_map_3 = new hash_open_addressing(100);
	while (mod_oa_map_3->get_load_factor() < 1)
	{
		mod_oa_map_3->add(key_mod(generate_random_key(100), 100), 1);
		cout << "\nload factor is: " << mod_oa_map_3->get_load_factor() << "  || collisions are: " << mod_oa_map_3->get_collisions();
	}

	/*******************************************************************************/
	/****** fourth experiment, with mid square and open addressing resolution ******/
	/*******************************************************************************/

	// table size 10
	cout << "\n\n\ncalculating results for mid square with open addressing resolution with table size 10...";

	hash_open_addressing* mid_square_oa_map_1 = new hash_open_addressing(10);
	while (mid_square_oa_map_1->get_load_factor() < 1)
	{
		mid_square_oa_map_1->add(key_mod(generate_random_key(10), 10), 1);
		cout << "\nload factor is: " << mid_square_oa_map_1->get_load_factor() << "  || collisions are: " << mid_square_oa_map_1->get_collisions();
	}

	// table size 25
	cout << "\n\n\ncalculating results for mid square with open addressing resolution with table size 25...";

	hash_open_addressing* mid_square_oa_map_2 = new hash_open_addressing(25);
	while (mid_square_oa_map_2->get_load_factor() < 1)
	{
		mid_square_oa_map_2->add(key_mod(generate_random_key(25), 25), 1);
		cout << "\nload factor is: " << mid_square_oa_map_2->get_load_factor() << "  || collisions are: " << mid_square_oa_map_2->get_collisions();
	}

	// table size 100
	cout << "\n\n\ncalculating results for mid square with open addressing resolution with table size 100...";

	hash_open_addressing* mid_square_oa_map_3 = new hash_open_addressing(100);
	while (mid_square_oa_map_3->get_load_factor() < 1)
	{
		mid_square_oa_map_3->add(key_mod(generate_random_key(100), 100), 1);
		cout << "\nload factor is: " << mid_square_oa_map_3->get_load_factor() << "  || collisions are: " << mid_square_oa_map_3->get_collisions();
	}

	cout << endl;
	return 0;
}