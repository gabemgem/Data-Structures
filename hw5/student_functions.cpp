#include <fstream>
#include <iostream>
#include <string>
#include "SongLibrary.h"

//////////////////DO NOT CHANGE THIS CODE////////////////////////

//Construct a Song object with values
Song::Song(const std::string& title, const std::string& artist, 
     const std::string& album, unsigned int year){
	this->title = title;
	this->artist = artist;
	this->album = album;
	this->year = year;
	used = false;
	this->song_group_ptr = NULL;
}

//Song equality doesn't depend on pointers or being used
bool operator== (const Song& s1, const Song& s2){
	return (s1.getYear() == s2.getYear()) && (s1.getTitle() == s2.getTitle())
          && (s1.getAlbum() == s2.getAlbum()) && (s1.getArtist() == s2.getArtist());
}

//Modifier for group pointer
void Song::updateSongGroupPointer(SongGroupNode* ptr){
	if(ptr){
		//Check that ptr is actually for this Song.
		assert(ptr->m_song->value == *this); 
		song_group_ptr = ptr;
	}
	else{
		song_group_ptr = NULL;
	}
}

//Make output easier by overload operator<<
std::ostream& operator<< (std::ostream& ostr, const Song& song){
	if(!song.getSongGroupPointer()){
		ostr << "\"" << song.getTitle() << "\" by " << song.getArtist() << " on \"" 
	       << song.getAlbum() << "\" (" << song.getYear() << ")" << std::endl;
	}
	else{
		ostr << "\"" << song.getTitle() << "\" by " << song.getArtist() << " on \"" 
		<< song.getAlbum() << "\" (" << song.getYear() << ")" << " in Song Group "
		<< song.getSongGroupPointer()->id << std::endl;
	}
	return ostr;
}

/////////////////////////YOUR CODE STARTS HERE/////////////////////////////////


//////////////////////////////GROUP FUNCTIONS/////////////////////////////////

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-id is the ID of the list we are searching for
BEHAVIOR:
None
RETURN:
NULL if no list matches the ID, otherwise returns the GroupListNode* containing
the head of the list with ID id.
*/
GroupListNode* GroupExists(GroupListNode* song_groups, GroupID id){
	if(song_groups!=NULL) {

		GroupListNode* ret = song_groups;//GroupListNode* to return

		if(ret->value->id==id)//if group to find is first group
			return ret;

		while(ret->ptr!=NULL) {//check other groups
			if(ret->value->id==id)
				return ret;
			ret=ret->ptr;
		}

		if(ret->value->id==id)//check last group
			return ret;
		
	}
	return NULL;//return null if group not found
}

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-id is the ID of the list we are creating
BEHAVIOR:
Add a new song group to song_groups, give the new song group ID id. Order of
song groups is not guaranteed.
RETURN:
None
*/
void MakeGroup(GroupListNode*& song_groups, GroupID id){

	if(GroupExists(song_groups, id)) {return;}//if the group already exists, do nothing

	GroupListNode* n = new GroupListNode;//new GroupListNode* to add
	SongGroupNode* s = new SongGroupNode;//new SongGroupNode* to put in n
	s->next_song_ptr=NULL;//initialize the SongGroupNode*
	s->prev_song_ptr=NULL;
	s->next_by_artist_ptr=NULL;
	s->prev_by_year_ptr=NULL;
	s->m_song=NULL;
	s->id=id;
	n->value=s;//initialize the GroupListNode*
	n->ptr=NULL;

	if(song_groups==NULL)//if first group
		song_groups=n;//set head of groups to new node
	
	else {
		if(song_groups->ptr==NULL)//if second group
			song_groups->ptr=n;//set next node after head to new node
		else {//otherwise put in spot after first group
			n->ptr=song_groups->ptr;
			song_groups->ptr=n;
		}
	}

		
}


/*
ARGUMENTS:
-group_head points to the head of a song group
-song is the Song we are checking the group for
BEHAVIOR:
None
RETURN:
If song is found in the group return true. If song is not found,
return false.
*/
bool SongInGroup(SongGroupNode* group_head, const Song& song){
	SongGroupNode* s = group_head;//SongGroupNode* to move through the group
	if(s==NULL) return false;//if there's nothing in the group return false
	if(s->next_song_ptr==NULL) {//if there's only one thing in the group
		if(s->m_song!=NULL && s->m_song->value==song)//and that thing is the song
			return true;
		return false;
	}
	while(s->next_song_ptr!=NULL) {//check all of the nodes
		if(s->m_song->value==song)
			return true;
		s=s->next_song_ptr;
	}
	if(s->m_song!=NULL && s->m_song->value==song)//check last node
		return true;
	return false;
}

/*
ARGUMENTS:
-library_ptr points to the LibraryNode* containing the Song we want to add.
-list_ptr is the head of the song group we want to add the song to.
BEHAVIOR:
Modify the group pointed to by list_ptr to reflect that the song is in the group.
This may change the length of the list. Modifies the Song's members as well.
RETURN:
None
*/
void AddToGroup(LibraryNode* library_ptr, GroupListNode* list_ptr){

	SongGroupNode* l = list_ptr->value;//SongGroupNode to move through the group

	if(!SongInGroup(list_ptr->value, library_ptr->value)) {
							//if song is already in the group do nothing
		

		if(list_ptr->value->m_song==NULL) {//if nothing in the group
			list_ptr->value->m_song=library_ptr;//put the song in the head of the group
			library_ptr->value.updateSongGroupPointer(list_ptr->value);//update song
			library_ptr->value.setUsedInGroup(true);
			return;
		}

		

		
		
		SongGroupNode* s = new SongGroupNode;//new SongGroupNode* to hold the song

		while(l->next_song_ptr!=NULL) {//move l to end of list while updating next_by_artist pointers
			if(l->next_by_artist_ptr==NULL && 
				l->m_song->value.getArtist()==library_ptr->value.getArtist())
				l->next_by_artist_ptr=s;
			l=l->next_song_ptr;
		}

		if(l->next_by_artist_ptr==NULL && //update last node's next_by_artist pointer
				l->m_song->value.getArtist()==library_ptr->value.getArtist())
				l->next_by_artist_ptr=s;

		l->next_song_ptr=s;//put s at the end of the list
		s->prev_song_ptr=l;

		s->m_song=library_ptr;//initialize s
		s->m_song->value.updateSongGroupPointer(s);
		s->m_song->value.setUsedInGroup(true);
		s->id=list_ptr->value->id;
		s->next_song_ptr=NULL;
		s->next_by_artist_ptr=NULL;
		s->prev_by_year_ptr=NULL;

		RecomputePrevByYear(list_ptr);//redo the prev_by_year pointers

	}



}

/*
ARGUMENTS:
-library_ptr points to the LibraryNode* containing the Song we want to remove from a group.
-song_groups points to a singly-linked list of song group heads
BEHAVIOR:
Modifies the Song's member variables to reflect that it is not in a group. Modifies the group
so that the Song is not in the group. This function may cause song_groups to be modified as well.
RETURN:
None
*/
void RemoveFromGroup(LibraryNode* library_ptr, GroupListNode* song_groups){
	while(song_groups!=NULL) {//cycle through all of the song groups


		if(library_ptr!=NULL && SongInGroup(song_groups->value, library_ptr->value)) {//if song is in the group

			if(song_groups->value->m_song==library_ptr) {//if song is in first node
				library_ptr->value.updateSongGroupPointer(NULL);//update the song
				library_ptr->value.setUsedInGroup(false);

				if(song_groups->value->next_song_ptr==NULL) {//if there is only one node
					song_groups->value->next_song_ptr=NULL;//set everything in the node to NULL
					song_groups->value->prev_song_ptr=NULL;
					song_groups->value->next_by_artist_ptr=NULL;
					song_groups->value->prev_song_ptr=NULL;
					song_groups->value->m_song=NULL;
				}
					
				else {//if there are other nodes
					SongGroupNode* s = song_groups->value;//temp node to delete
					song_groups->value=s->next_song_ptr;//move head along the list
					s->next_song_ptr=NULL;//delete s
					s->prev_song_ptr=NULL;
					s->next_by_artist_ptr=NULL;
					s->prev_by_year_ptr=NULL;
					s->m_song=NULL;
					delete s;
				}
			}

			else {//if the song isn't in the first node
				SongGroupNode* s = song_groups->value;//SongGroupNode* to stay at the front
				SongGroupNode* song = song_groups->value;//SongGroupNode* to find the song
				while(song->next_song_ptr!=NULL) {//find the song
					if(song->m_song->value==library_ptr->value)
						break;
					song=song->next_song_ptr;
				}


				if(song->next_song_ptr==NULL) {//if the song is the last node
					song->prev_song_ptr->next_song_ptr=NULL;//take song out of the list
					song->m_song->value.updateSongGroupPointer(NULL);//update the song
					song->m_song->value.setUsedInGroup(false);
					
				}

				else {//if the song is in the middle
					SongGroupNode* p = song->prev_song_ptr;//previous SongGroupNode*
					SongGroupNode* n = song->next_song_ptr;//next SongGroupNode*
					p->next_song_ptr=n;//take song out of the list
					n->prev_song_ptr=p;
					song->m_song->value.updateSongGroupPointer(NULL);//update song
					song->m_song->value.setUsedInGroup(false);
				}

				if(s->next_by_artist_ptr==song)//update next_by_artist pointers
					s->next_by_artist_ptr=song->next_by_artist_ptr;
				while(s->next_song_ptr!=NULL)
				{
					s=s->next_song_ptr;
					if(s->next_by_artist_ptr==song) {
						s->next_by_artist_ptr=song->next_by_artist_ptr;
						break;
					}
				}

				song->next_song_ptr=NULL;//delete song
				song->prev_song_ptr=NULL;
				song->next_by_artist_ptr=NULL;
				song->prev_by_year_ptr=NULL;
				song->m_song=NULL;
				delete song;
				RecomputePrevByYear(song_groups);//redo the prev_by_year pointers
				return;
			}
		}
		song_groups=song_groups->ptr;//iterate to next song group if song is not found
	}



}

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-list_ptr1 contains to the song group head of Group A
-list_ptr2 contains the song group head of Group B
BEHAVIOR:
Modify Group A so that at the end of its songs, the songs of Group B are added in the same
order they were found in Group B. Remove the now-empty Group B.
RETURN:
None
*/
void CombineGroups(GroupListNode*& song_groups, GroupListNode*& list_ptr1, GroupListNode*& list_ptr2){
	SongGroupNode* s = list_ptr2->value;//SongGroupNode* to move through the second group

	while(s!=NULL) {//put all songs in first group
		AddToGroup(s->m_song, list_ptr1);
		s=s->next_song_ptr;
	}

	RemoveGroup(song_groups, list_ptr2);//delete second group
}

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-list_ptr is the head of the song group we want to remove.
BEHAVIOR:
Remove the group from the list of song groups. No Song objects should remain associated with the
group, and the function should modify Song member variables appropriately to reflect this. Any
memory associated with the group must be released.
RETURN:
None
*/
void RemoveGroup(GroupListNode*& song_groups, GroupListNode* list_ptr){
	if(song_groups==NULL || list_ptr==NULL) return;//if anything is already null
	
	SongGroupNode* s = list_ptr->value;//SongGroupNode* to move through the list

	while(s!=NULL) {//delete all of the songs in the list
			
		SongGroupNode* n = s;//Node to delete
		s=s->next_song_ptr;//iterate s so it doesn't get deleted
		RemoveFromGroup(n->m_song, song_groups);//delete the song
		
		
	}


	GroupListNode* iter = song_groups;//GroupListNode* to move through the list

	if(song_groups==list_ptr) {//if list_ptr is the first node
		if(song_groups->ptr)//if there is a next node
			song_groups=song_groups->ptr;//iterate the head of the group
		delete list_ptr->value;//delete list_ptr and its SongGroupNode*
		delete list_ptr;
	}

	else {//if list_ptr is not the first node
		while(iter!=NULL) {
			if(iter->ptr==list_ptr) {//if the next node is list_ptr
				iter->ptr=list_ptr->ptr;//iter's next node is the node after list_ptr
				delete list_ptr->value;//delete list_ptr and its SongGroupNode*
				delete list_ptr;
				return;//End the loop
			}
			iter=iter->ptr;
		}
	}
}

/*
ARGUMENTS:
-list_ptr is the head of the song group we want to add the song to.
BEHAVIOR:
Recompute all prev_by_year_ptr members in the song group pointed to by
list_ptr.
RETURN:
None
*/
void RecomputePrevByYear(GroupListNode* list_ptr){
	SongGroupNode* s = list_ptr->value;//SongGroupNode* to move through the group

	while(s!=NULL) {//iterate through the group
		s->prev_by_year_ptr=NULL;//delete old prev_by_year pointer
		if(s->prev_song_ptr!=NULL) {//if there is a previous node
			SongGroupNode* check = s->prev_song_ptr;//node to check previous nodes
			while(check!=NULL) {//go through previous nodes
				if(check->m_song->value.getYear()<s->m_song->value.getYear()) {
					s->prev_by_year_ptr=check;//set s's prev_by_year pointer to check if correct
					break;
				}
				check=check->prev_song_ptr;//iterate check
			}

		}
		s=s->next_song_ptr;//iterate s
	}

}

////////////////////////////PRINT FUNCTIONS////////////////////////////////////

/*
ARGUMENTS:
-library_head points to the first LibraryNode* of the song library
-print_file points to an ostream to print output to
BEHAVIOR:
Print each song in the library in the order it was added.
RETURN:
None
*/
void PrintLibrary(LibraryNode* library_head,std::ostream& print_file){
	int count = 0;//int to keep track of # of songs
	while(library_head!=NULL) {//go through the whole library
		print_file<<library_head->value;//print the songs
		library_head=library_head->ptr;
		count++;//increase count
	}
	print_file<<"Library contains "<<count<<" song(s)\n";
}

/*
ARGUMENTS:
-group_head points to the first SongGroupNode* of the group to print
-print_file points to an ostream to print output to
BEHAVIOR:
Print each song in the group in the order it was added.
RETURN:
None
*/
void PrintGroupSequential(SongGroupNode* group_head,std::ostream& print_file){
	int count = 0;//int to keep track of # of songs in group
	SongGroupNode* iter = group_head;//SongGroupNode* to move through the group
	print_file<<"List ID "<<iter->id<<" contains:\n";
	while(iter!=NULL) {//move through the whole group
		
		if(iter->m_song!=NULL) {//if there is a song
			print_file<<iter->m_song->value;//print it
			count++;//and increase count
		}
		iter=iter->next_song_ptr;
		
	}
	print_file<<count<<" song(s)\n";//print # of songs
}

/*
ARGUMENTS:
-group_ptr points to the location in a particular song group to start printing from
-print_file points to an ostream to print output to
BEHAVIOR:
Print a rewind list by following the prev_by_year_ptr pointers, starting from the song
pointed to by group_ptr.
RETURN:
None
*/
void PrintGroupRewind(SongGroupNode* group_ptr,std::ostream& print_file){
	int count=0;//int to keep track of # of songs
	print_file<<"Rewind list for "<<group_ptr->m_song->value.getYear()<<std::endl;
	while(group_ptr!=NULL) {//go through whole rewind list
		count++;//increase count
		print_file<<"\t#"<<count<<": "<<group_ptr->m_song->value;//print out the song
		group_ptr=group_ptr->prev_by_year_ptr;//and move to next prev_by_year node
	}
	print_file<<"Rewind list contained "<<count<<" song(s).\n";//print size of r.list
}

/*
ARGUMENTS:
-group_ptr points to the location in a particular song group to start printing from
-print_file points to an ostream to print output to
BEHAVIOR:
Print a rewind list by following the next_by_artist_ptr pointers, starting from the song
pointed to by group_ptr.
RETURN:
None
*/
void PrintGroupMarathon(SongGroupNode* group_ptr,std::ostream& print_file){
	print_file<<"Marathon list for "<<group_ptr->m_song->value.getArtist()<<std::endl;
	int count = 0;//int to keep track of # of songs in marathon list
	while(group_ptr!=NULL) {//go through whole m.list
		count++;//increase count
		print_file<<"\t#"<<count<<": "<<group_ptr->m_song->value;//print out the song
		group_ptr=group_ptr->next_by_artist_ptr;//and move to next next_by_artist node
	}
	print_file<<"Marathon list contained "<<count<<" song(s).\n";//print size of m.list
}

/*
ARGUMENTS:
-group_head points to the first SongGroupNode* of the group to analyze
-print_file points to an ostream to print output to
BEHAVIOR:
Find the rewind list with the most songs in the song group pointed to by group_head.
Print the rewind list and the song count to print_file.
RETURN:
None
*/
void PrintLongestGroupRewind(GroupListNode* group_head,std::ostream& print_file){
	int max=0, count=0;//ints for each rewind list size and max rewind list size

	SongGroupNode* s = group_head->value;//SongGroupNode to move through the list
	SongGroupNode* m = group_head->value;//SongGroup Node of max rewind list size

	while(s!=NULL) {//move s through the whole list
		if(s->prev_by_year_ptr!=NULL) {//if s has a prev_by_year SongGroupNode*
			SongGroupNode* c = s->prev_by_year_ptr;//SongGroupNode to check prev_by_year's
			count+=2;//add 2 to count b/c r.list now includes s and c
			while(c->prev_by_year_ptr!=NULL) {//check through all prev_by_year's starting with c
				c=c->prev_by_year_ptr;
				count++;
			}
			if(count>max) {//if this rewind list is bigger than the max r.list
				max=count;//update max to new max list size
				m=s;//set m to the head of the r.list
			}
		}
		s=s->next_song_ptr;//move along s
		count=0;//reset count
	}

	if(max>0) {//if found a r.list
		print_file<<"Maximum size rewind list is for year "
				  <<m->m_song->value.getYear()<<std::endl;
		int co = 0;//int to number songs in r.list
		while(m!=NULL) {//move through the r.list printing songs
			co++;
			print_file<<"\t#"<<co<<": "<<m->m_song->value;
			m=m->prev_by_year_ptr;
		}
	}	
	print_file<<"Longest rewind list contained "<<max<<" song(s).\n";//print size of list
	
}

///////////////////////////////CLEANUP/////////////////////////////////////////

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
BEHAVIOR:
Delete every group. Do not leak. Modifies all groups and the song_groups list.
Update every Song to reflect not being in a group.
RETURN:
None
*/
void DeleteAllSongGroups(GroupListNode*& song_groups){
	if(song_groups!=NULL) {//if there is something in song_groups
		while(song_groups->ptr!=NULL) {//delete the next node from head of list
			GroupListNode* g = song_groups->ptr;//next node to be deleted
			RemoveGroup(song_groups, g);//delete g
		}

		GroupListNode* g = song_groups->ptr;
		if(song_groups!=NULL && g!=NULL);//make sure last node is deleted
			RemoveGroup(song_groups, g);
		if(song_groups!=NULL)//make sure the head is deleted
			RemoveGroup(song_groups, song_groups);

		
		
	}
}
