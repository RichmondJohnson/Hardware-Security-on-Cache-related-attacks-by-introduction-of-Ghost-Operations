Welcome to the Hardware-Security-on-Cache-related-attacks-by-introduction-of-Ghost-Operations wiki!

Aim and Motivation – shortfalls in current mapping techniques in many-core mapping algorithms

# Novel algorithms for application mapping in many core architectures tend to focus on improving performance and efficiency by assigning specific functionalities to localized nodal clusters
# Although it may achieve its designated goals in terms of speed, one cannot deny that it leverages predictable patterns of the system behavior, and this when exploited by an external/internal attacker can lead to a blueprint of the internal mapping architecture being exposed
# The attacker (depending on his type – either a memory or cache or even a processor blocking attacker) may then choose to attack a particular cluster set For example, there may be a particular cluster dedicated to performing only memory (either L2, L3 or Main Memory) transactions and therefore accessing the cache contents of this cluster may expose the data exchanges being performed by the system as a whole
# In another case, even if the memory access is evenly distributed across the clusters, an attacker manages to read the cache contents is able to know what data is being processed/exchanged by each individual clusters
Therefore from the above points, it can be definitively concluded that an insight into the cache is equivalent to exposing the system behavior as a whole up to the level of instruction level data exchanges
# Even if the mapping algorithms are perfect such that functionalities are distributed evenly across clusters, an attack on the cache still exposes the system
# It becomes necessary to protect the cache contents as it is the entry point for a number of attacks
# In this project, we explore the cache related attacks in multi-nodal multi core systems and make best efforts to provide safety against such attacks

python secureexec.py $filename.c -secexec=ON/OFF   -> $filename.c (name of c program file)
it will run the tool and generate result_file.csv
In copy that file and template_sheet in a windows folder
(1) Launch template_sheet.xlsm
(2) Developer -> Macros -> Click on the first item in the list
(3) Click Run
(4) Choose the location where we've put the .csv file
