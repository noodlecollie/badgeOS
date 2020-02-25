#include "PartitionDump.h"
#include "heltec.h"
#include "esp_partition.h"

namespace BadgeOS
{
	namespace PartitionDump
	{
		static void dumpPartitions(esp_partition_type_t type, const char* identifier)
		{
			Serial.printf("*** %s partitions:\r\n", identifier);

			for ( esp_partition_iterator_t iterator = esp_partition_find(type, ESP_PARTITION_SUBTYPE_ANY, nullptr);
				  iterator;
				  iterator = esp_partition_next(iterator) )
			{
				const esp_partition_t* partition = esp_partition_get(iterator);

				Serial.printf("      Label: '%s'\r\n", partition->label);
				Serial.printf("    Subtype: 0x%x\r\n", partition->subtype);
				Serial.printf("    Address: 0x%08x\r\n", partition->address);
				Serial.printf("       Size: 0x%x (%u) bytes\r\n", partition->size, partition->size);
				Serial.printf("  Encrypted: %s\r\n", partition->encrypted ? "true" : "false");
				Serial.println("");
			}
		}

		void dumpPartitionInfo()
		{
			dumpPartitions(ESP_PARTITION_TYPE_APP, "App");
			dumpPartitions(ESP_PARTITION_TYPE_DATA, "Data");
		}
	}
}
