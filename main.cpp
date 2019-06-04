#include "cache.h"
#include <fstream>
#define lookup 1
#define L1_hit_latency lookup
#define L1_miss_latency 2 //cacti
#define L2_hit_latency L1_miss_latency
#define L2_miss_latency 3 //cacti
using namespace std;


int main(int argc, char** argv)
{
	
	Cache attacker_l1(1);
	Cache l2(2);
	Cache victim_l1(1);
	
	ifstream attacker_trace;
	attacker_trace.open(argv[1]);
	ifstream victim_trace;
	victim_trace.open(argv[2]);
	string rw;
	unsigned int addr;
	bool attacker_l1_evict_dirtybit;
	unsigned int attacker_l1_evict_addr;
	bool victim_l1_evict_dirtybit;
	unsigned int victim_l1_evict_addr;
	bool l2_evict_dirtybit;
	unsigned int l2_evict_addr;
	unsigned int attacker_time_original[L2_no_of_blocks];
	unsigned int attacker_time_new[L2_no_of_blocks];
	unsigned int k=0;

	vector<unsigned int> l2_blocks_accessed_by_attacker;	
	
	while(!attacker_trace.eof())
	{
		attacker_trace >> rw;
		attacker_trace >> std::hex >> addr;

		l2_blocks_accessed_by_attacker.push_back(addr);

		if(attacker_trace.eof())
			break;

		if(attacker_l1.cache_search(addr)==1)
		{
			attacker_l1.cache_install(addr, rw, attacker_l1_evict_dirtybit, attacker_l1_evict_addr);
			attacker_time_original[k]=L1_hit_latency;	
		}

		else
		{
			attacker_l1.cache_install(addr, rw, attacker_l1_evict_dirtybit, attacker_l1_evict_addr);
			if(l2.cache_search(addr)==1)
			{
				attacker_time_original[k]=L2_hit_latency;
			}
			else
			{
				attacker_time_original[k]=L2_miss_latency;
			}	
			l2.cache_install(addr, rw, l2_evict_dirtybit, l2_evict_addr);
			if(attacker_l1_evict_dirtybit==1)
			{
				l2.cache_install(attacker_l1_evict_addr, "w", l2_evict_dirtybit, l2_evict_addr);
			}
			
		}
	k++;
	}

	l2.clflush();
	attacker_l1.clflush();

	/*for(unsigned int x=0;x<L2_no_of_blocks;x++)
	{
		cout<<"Block"<<x<<" "<< attacker_time_original[x]<<endl;
	}*/







	while(!victim_trace.eof())
	{
		victim_trace >> rw;
		victim_trace >> std::hex >> addr;

		if(victim_trace.eof())
			break;

		if(victim_l1.cache_search(addr)==1)
		{
			victim_l1.cache_install(addr, rw, victim_l1_evict_dirtybit, victim_l1_evict_addr);
		}

		else
		{
			victim_l1.cache_install(addr, rw, victim_l1_evict_dirtybit, victim_l1_evict_addr);
			l2.cache_install(addr, rw, l2_evict_dirtybit, l2_evict_addr);
			if(victim_l1_evict_dirtybit==1)
			{
				l2.cache_install(victim_l1_evict_addr, "w", l2_evict_dirtybit, l2_evict_addr);
			}
			
		}
	}


	attacker_trace.close();

	attacker_trace.open(argv[1]);
	k=0;

	while(!attacker_trace.eof())
	{
		attacker_trace >> rw;
		attacker_trace >> std::hex >> addr;

		if(attacker_trace.eof())
			break;

		if(attacker_l1.cache_search(addr)==1)
		{
			attacker_l1.cache_install(addr, rw, attacker_l1_evict_dirtybit, attacker_l1_evict_addr);
			attacker_time_new[k]=L1_hit_latency;	
		}

		else
		{
			attacker_l1.cache_install(addr, rw, attacker_l1_evict_dirtybit, attacker_l1_evict_addr);
			if(l2.cache_search(addr)==1)
			{
				attacker_time_new[k]=L2_hit_latency;
			}
			else
			{
				attacker_time_new[k]=L2_miss_latency;
			}	
			l2.cache_install(addr, rw, l2_evict_dirtybit, l2_evict_addr);
			if(attacker_l1_evict_dirtybit==1)
			{
				l2.cache_install(attacker_l1_evict_addr, "w", l2_evict_dirtybit, l2_evict_addr);
			}
			
		}
	k++;
	}

	ofstream result_file;
	result_file.open("result_file.csv");
	result_file << "BlockID,Address,New_access_time,Old_access_time\n";

	for(unsigned int y=0;y<L2_no_of_blocks;y++)
	{
		/*if(attacker_time_new[y]!=attacker_time_original[y])
		{
			cout<<"Block"<<y<<" "<< attacker_time_new[y]<<" "<<attacker_time_original[y]<<endl;
		}*/
//	result_file << "Block"<<y<<"\t"<<attacker_time_new[y]<<"\t\t"<<attacker_time_original[y]<<"\n";

	result_file << "Block"<<y<<",0x"<<std::hex<<l2_blocks_accessed_by_attacker[y]<<std::dec<<","<<attacker_time_new[y]<<","<<attacker_time_original[y]<<"\n";

	
	}


	victim_trace.close();
	attacker_trace.close();
	result_file.close();
return 0;

}

