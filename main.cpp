#include <stdlib.h>
#include <stdio.h>
#include "coordinate.h"
#include <cmath>
#include <limits>
#include <iostream>
using namespace std;


class Coordinate_DoubleLinkedList{

private:
	
	Coordinate* head;
	Coordinate* tail;
	
	int length;

public:
	Coordinate_DoubleLinkedList(){
	head = nullptr;
	tail = nullptr;
	length = 0;
	}

	Coordinate* get_head(){
		return head;
	}

	Coordinate* get_tail(){
		return tail;
	}

	

	//add coordinate to end of linked list
	void add_coordinate(Coordinate *list_end, float x, float y){

		int coord_id = length+1;
		Coordinate* newCoordinate = 
		(Coordinate*)malloc(sizeof(Coordinate));
		newCoordinate->coord_id = length+1;
		newCoordinate->x =x;
		newCoordinate->y = y;
		newCoordinate->next = nullptr;
		newCoordinate->previous = tail;

		if (head ==nullptr){
			head = tail = newCoordinate;
		} else {
			tail->next = newCoordinate;
			newCoordinate->previous = tail;
			tail = newCoordinate;		
		}
		length++;
	}	


	//displays all coordinates from beginning to end
	void forward_display(Coordinate *list_beginning){
		
		Coordinate* temp = head;		

		while (temp != nullptr){
			cout << temp->x <<","<< temp->y <<endl;
			temp = temp->next;
		}


	}	

	//displays all coordinates from end to beginning
	void backward_display(Coordinate *list_end){
		Coordinate* temp = head;
		while (temp !=nullptr){
			cout << temp->x <<","<< temp->y <<endl;
			temp = temp->previous;
		}


	}


	void delete_coordinate(Coordinate *list_beginning, 
				int coord_id_to_delete){
		
		Coordinate* current = head;
		//searching for coord_id
		while (current != nullptr &&
			current->coord_id != coord_id_to_delete){
			current	= current->next;
		}
		
		// to ensure that head is not a null pointer
		if (current==head){
			head = current->next;
			if (head !=nullptr){
				head->previous = nullptr;
			}
		}

		// to ensure that the tail is not null
		if (current == tail){
			tail = current->previous;
			if (head !=nullptr){
				tail->next = nullptr;
			}
		}
		
		//freeing memory
		delete current;
		
		//decrease length by one
		length--;
	}
	
	int list_length(Coordinate *list_beginning, float x, float y){
		int count=0;
		Coordinate* current = list_beginning;
		
		//traverses list and count increments;
		while (current != nullptr){
			count ++;
			current = current->next;
		}

		return count;

	}

	void closest_to(Coordinate *list_beginning, float x, float y){
		Coordinate* current = list_beginning;
		Coordinate* closest = nullptr;

		//the min distance coordinate of our list
		float min_distance = 
			sqrt
			(
				pow(current->x-x, 2) +
				pow(current->y-y, 2)

			);

		//traversing list, if distance of coordiate less than the 
		//min_distance, then the distance is reassigned

		while (current != nullptr){
			float current_distance = 
			sqrt
				(
				pow(current->x-x, 2) + 
				pow(current->y-y, 2)
				);
		
			if (current_distance < min_distance){
				current_distance = min_distance;
				closest=current;
			}
			current = current->next;
			
		}

		if (closest != nullptr){
			cout << "Closest: " 
			<< closest->x
			<< "," 
			<< closest->y
			<< endl; 
		}	
	}
};

int main(int argc, char* argv[]) {

	int n = atoi(argv[1]);
	srand(time(0));
	
	Coordinate_DoubleLinkedList list;
	for (int i = 0; i < n; i++){
		float random_x = static_cast<float>(rand() % 100);
		float random_y = static_cast<float>(rand() % 100);
		list.add_coordinate(list.get_tail(), random_x, random_y);
	}

	list.forward_display(list.get_head());
	list.backward_display(list.get_tail());

	
	float input_x;
	float input_y;
	cout << "\nEnter an x coord: ";
	cin >> input_x;
	cout << "\nEnter a y coord: ";
	cin >> input_y;
	list.closest_to(list.get_head(), input_x, input_y);

	float coordinate_to_delete;
	cout << "\nEnter the coord id to delete: ";
	int coord_id_to_delete;
	cin >> coord_id_to_delete;
	list.delete_coordinate(list.get_head(), coord_id_to_delete);
	cout << "\nUpdated List\n";
	list.forward_display(list.get_head());
	
	return 0;
}
