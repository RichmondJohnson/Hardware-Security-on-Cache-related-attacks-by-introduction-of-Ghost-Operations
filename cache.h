#include <iostream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;
#define L1_size   8192
#define L1_assoc  4 
#define L1_blocksize   32
#define L1_sets ((L1_size)/(L1_blocksize*L1_assoc))
#define L2_size   131072
#define L2_assoc  8 
#define L2_blocksize   L1_blocksize
#define L2_sets ((L2_size)/(L2_blocksize*L2_assoc))
#define L2_no_of_blocks (L2_size/L2_blocksize)
//#define DEBUG_MODE    //uncomment for debug mode

//MSI protocol variables
enum State
{
	M,
	S,
	I		
};

class Coherence_Info
{
	protected:
	State state;
	public:
	virtual void set_state(State state)=0;
	virtual State get_state() {return state;}
};
//Class to initialize a Cache block
class Tag_Block : public Coherence_Info
{
	private:
	// valid -> to check if the value in cache block is valid or invalid
	// dirty -> to check if the value in cache block is modified from previous value or not
	// lru_counter -> to check the least recently used cache block in a set which is used for replacement policy
	//tag -> value stored in a cache block
	//state -> whether the block in M, S or I state as per MSI protocol
	//block_info -> in which block/column of a set is the cache block present
	bool valid,dirty;
	unsigned int lru_counter;
	unsigned int tag;
	unsigned int block_info;
	
	friend class Cache;

	public:
	Tag_Block()
	{
		valid =0;
		dirty =0;
		tag =0;
		lru_counter =0;
		state = I;
		block_info=0;
	}

	void set_valid()
	{
		valid = 1;
	}

	void clear_valid()
	{
		valid = 0;
	}

	bool is_valid()
	{
		return valid;
	}
	void set_dirty()
	{
		dirty = 1;
	}

	void clear_dirty()
	{
		dirty = 0;
	}

	bool is_dirty()
	{
		return dirty;
	}

	void set_lru_counter(unsigned int count)
	{
		lru_counter = count;
	}
	
	unsigned int get_lru_counter()
	{
		return lru_counter;
	}
	
	void set_tag(unsigned int tags)
	{
		tag= tags;
	}

	unsigned int get_tag()
	{
		return tag;
	}

	void set_state(State states)
	{
		state = states;
	}

	State get_state()
	{
		return state;
	}

	void set_block(unsigned int block)
	{
		block_info = block;
	}

	inline unsigned int get_block()
	{
		return block_info;
	}

	void copy_Block(Tag_Block& block1)
	{
		this->valid = block1.valid;
		this->dirty =block1.dirty;
		this->tag =block1.tag;
		this->lru_counter =block1.lru_counter;
		this->state = block1.state;
		this->block_info=block1.block_info;
	}
};

//Class to initialise a cache
class Cache
{
	//global_lru_counter -> counter which will be used to initialse lru_counter
	//miss/hit -> to check if given tag value matches with value cache block or not
	//my_blocksize -> block size of L1 or L2 cache
	//my_sets -> no.of sets of L1 or L2 cache
	//my_assoc -> associativity of L1 or L2 cache
	public:
	unsigned int global_lru_counter;
	unsigned int miss, hit;
	unsigned int my_blocksize,my_sets,my_assoc;
	
	//Initialise a 2D Tag_array of Tag_block type to form a cache level of size Li_sets*Li_assoc
	Tag_Block*** Tag_array;

	Cache(unsigned int Level)
	{
		global_lru_counter=0;
		miss =0;
		hit = 0;
		if(Level==1)
		{
			my_blocksize=L1_blocksize;
			my_sets=L1_sets;
			my_assoc=L1_assoc;
			Tag_array = new Tag_Block**[L1_sets];
			
			for(unsigned int i=0; i< L1_sets; i++)
			{
				Tag_array[i]= new Tag_Block*[L1_assoc];
				for( unsigned int j=0; j<L1_assoc; j++)
				{
					Tag_array[i][j] = new Tag_Block();
				}
			}
		}
		else if(Level==2)
		{
			my_blocksize=L2_blocksize;
			my_sets=L2_sets;
			my_assoc=L2_assoc;
			Tag_array = new Tag_Block**[L2_sets];
			
			for(unsigned int i=0; i< L2_sets; i++)
			{
				Tag_array[i]= new Tag_Block*[L2_assoc];
				for( unsigned int j=0; j<L2_assoc; j++)
				{
					Tag_array[i][j] = new Tag_Block();
				}
			}

		}	
	}

	//find block bits from a given address
	unsigned int get_blockbits(unsigned int address)
	{
		#ifdef DEBUG_MODE
		cout<<"Debug: Blockbits "<<(address%my_blocksize)<<endl;
		#endif
		return (address%my_blocksize);
	}

	//find set bits from a given address
	unsigned int get_setbits(unsigned int address)
	{
		unsigned int set_info;
		set_info=(address/my_blocksize);
		set_info = (set_info & (my_sets -1));
		#ifdef DEBUG_MODE
		cout<<"Debug: Setbits "<<set_info<<endl;
		#endif
		return set_info;	
	}

	//find tag bits from a given address
	unsigned int get_tagbits(unsigned int address)
	{
		#ifdef DEBUG_MODE
		cout<<"Debug: Tagbits "<<((address)/(my_blocksize*my_sets))<<endl;
		#endif
		return ((address)/(my_blocksize*my_sets));
	} 
	
	//search a given tag in a cache by indexing using the set and block bits
	bool cache_search(unsigned int search_tag,unsigned int search_set,unsigned int& block_column)
	{
		//search in a set for all blocks and return 1 if a given tag matches with any valid value for a block, otherwise return 0
		for(unsigned int k=0; k< my_assoc; k++)
		{
			if((Tag_array[search_set][k]->get_tag() == search_tag) && (Tag_array[search_set][k]->is_valid()))
			{
				Tag_array[search_set][k]->set_lru_counter(global_lru_counter);
				block_column=k;
				#ifdef DEBUG_MODE
				cout<<"Debug: Cache Search Found"<<endl;
				#endif
				return 1;
			}		
		}
		#ifdef DEBUG_MODE
		cout<<"Debug: Cache Search Not Found"<<endl;
		#endif
		return 0;	
	}

	bool cache_search(unsigned int address)
	{
		unsigned int search_tag, search_set, block_column;
		search_tag = get_tagbits(address);
		search_set = get_setbits(address);
		//search in a set for all blocks and return 1 if a given tag matches with any valid value for a block, otherwise return 0
		bool result;
		result = cache_search(search_tag, search_set, block_column);
		#ifdef DEBUG_MODE
		cout<<"Debug: Cache Search Found :"<<result<<endl;
		#endif

	return result;	
	}

	//find an empty block using valid bit in a given set 
	bool search_in_set(unsigned int search_set,unsigned int& block_column)
	{
		for(unsigned int k=0;k<my_assoc;k++)
		{
			if((Tag_array[search_set][k]->is_valid()==0))
			{
					block_column = k;
					#ifdef DEBUG_MODE
					cout<<"Debug: Empty Block in Set Found"<<endl;
					#endif
					return 1;
			}
		}
	#ifdef DEBUG_MODE
	cout<<"Debug: Empty Block in Set Not Found"<<endl;
	#endif
	return 0;
	}

	//Find the least recently used block in a given full set.
	bool search_in_full_set(unsigned int search_set,unsigned int& block_column)
	{
		unsigned int smallest_block_column=0;
		unsigned int smallest_lru_counter = Tag_array[search_set][smallest_block_column]->get_lru_counter();
		for(unsigned int k=1;k<my_assoc;k++)
		{
				
			if(Tag_array[search_set][k]->get_lru_counter()< smallest_lru_counter)
			{
				smallest_block_column=k;
				smallest_lru_counter = Tag_array[search_set][smallest_block_column]->get_lru_counter();					
			}	
		}
	block_column = smallest_block_column;
	return 0;
	}		
	
	//reconstruct the address using set, block and tag bits which is used by L2 cache when a block is eveicted from L1 cache
	unsigned int address_reconstruct(unsigned int search_tag,unsigned int search_set)
	{
		unsigned int evict_address=0;
		evict_address = ((search_tag*my_sets)+search_set)*my_blocksize;
	#ifdef DEBUG_MODE
	cout<<"Debug: Evict Address "<<evict_address<<endl;
	#endif
	return evict_address;
	}

	//function to install a cache block in cache	
	unsigned int cache_install(unsigned int address, string rw, bool& evict_dirty,unsigned int& evict_address)
	{
		#ifdef DEBUG_MODE
		cout<<"Debug: Install Address "<<address<<endl;
		#endif
		unsigned int search_set, search_tag;
		global_lru_counter++;
		search_tag = get_tagbits(address);	
		search_set = get_setbits(address);
//		search_blockbits = get_blockbits(address);
		unsigned int block_column;
		evict_dirty=0;
		evict_address=0;

		//check if a given tag matches with value present in cache using cache_search function
		if(cache_search(search_tag, search_set,block_column))
		{
			hit++;
			Tag_array[search_set][block_column]->set_lru_counter(global_lru_counter);
			//If the value needs to be modified, set the dirty bit for that block			
			if(rw=="w")
			{
				Tag_array[search_set][block_column]->set_dirty();	
			}
		return 0;	
		}

		//If the given tag not found in cache
		else
		{
			miss++;
			//search if a block is free in the set and install the new tag in that block and set valid and lru_counter
			if(search_in_set(search_set, block_column))
			{
				Tag_array[search_set][block_column]->set_tag(search_tag);
				Tag_array[search_set][block_column]->set_valid();
				Tag_array[search_set][block_column]->set_lru_counter(global_lru_counter);
				//If the value needs to be modified, set the dirty bit for that block
				if(rw=="w")
				{
					Tag_array[search_set][block_column]->set_dirty();
				}
			return 0;			
			}

			//if the set is full, find the least recently used tag and recontruct the evict address from the value already stored(which is used by L2 cache). Then save the new tag and set lru_counter and valid bits and clear dirty bit
			else
			{
				search_in_full_set(search_set, block_column);
				evict_address = address_reconstruct(Tag_array[search_set][block_column]->get_tag() , search_set);		
				evict_dirty = Tag_array[search_set][block_column]->is_dirty();
				Tag_array[search_set][block_column]->clear_dirty();
				Tag_array[search_set][block_column]->set_tag(search_tag);
				Tag_array[search_set][block_column]->set_lru_counter(global_lru_counter);
				Tag_array[search_set][block_column]->set_valid();
				//If the value needs to be modified, set the dirty bit for that block
				if(rw=="w")
				{
					Tag_array[search_set][block_column]->set_dirty();
				}
			return 0;	
			}		
		}			

	}

	void clflush()
	{
		for(unsigned int i=0;i<my_sets;i++)
		{
			for(unsigned int j=0;j<my_assoc;j++)
			{
				Tag_array[i][j]->clear_valid();
			}
		}
	}


};
