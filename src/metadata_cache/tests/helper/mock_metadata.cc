/*
  Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; version 2 of the License.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "mock_metadata.h"

#include <map>
#include <memory>
#include <vector>

#include "mysqlrouter/metadata_cache.h"


using namespace std;

namespace metadata_cache {
  /**
   * Compare two server objects found in the metadata server.
   */
  bool operator == (const metadata_cache::ManagedInstance & s1, const metadata_cache::ManagedInstance & s2) {
    return (s1.replicaset_name == s2.replicaset_name &&
            s1.mysql_server_uuid == s2.mysql_server_uuid &&
            s1.host == s2.host &&
            s1.port == s2.port &&
            s1.xport == s2.xport &&
            s1.mode == s2.mode &&
            s1.role == s2.role &&
            s1.weight == s2.weight &&
            s1.location == s2.location &&
            s1.version_token == s2.version_token);
  }
}

/** @brief Constructor
 * @param bootstrap_servers The servers that store the metadata.
 * @param user The user name used to authenticate to the metadata server.
 * @param password The password used to authenticate to the metadata server.
 * @param connection_timeout The time after which a connection to the
 *                           metadata server should timeout.
 * @param connection_attempts The number of times a connection to metadata must
 *                            be attempted, when a connection attempt fails.
 *
 */
MockNG::MockNG(const std::string &user, const std::string &password,
               int connection_timeout, int connection_attempts,
               unsigned int ttl)
  : ClusterMetadata(user, password, connection_timeout, connection_attempts, ttl) {
  ms1.replicaset_name = "replicaset-1";
  ms1.mysql_server_uuid = "instance-1";
  ms1.location = "us.wa.seattle";
  ms1.host = "host-1";
  ms1.port = 3306;
  ms1.xport = 33060;
  ms1.mode = metadata_cache::ServerMode::ReadWrite;
  ms1.role = "master";
  ms1.weight = 1;
  ms1.version_token = 0;

  ms2.replicaset_name = "replicaset-1";
  ms2.mysql_server_uuid = "instance-2";
  ms2.location = "us.ca.cupertino";
  ms2.host = "host-2";
  ms2.port = 3306;
  ms2.xport = 33060;
  ms2.mode = metadata_cache::ServerMode::ReadWrite;
  ms2.role = "master";
  ms2.weight = 1;
  ms2.version_token = 0;

  ms3.replicaset_name = "replicaset-1";
  ms3.mysql_server_uuid = "instance-3";
  ms3.location = "us.wi.madison";
  ms3.host = "host-3";
  ms3.port = 3306;
  ms3.xport = 33060;
  ms3.mode = metadata_cache::ServerMode::ReadOnly;;
  ms3.role = "scale-out";
  ms3.weight = 1;
  ms3.version_token = 0;

  ms4.replicaset_name = "replicaset-2";
  ms4.mysql_server_uuid = "instance-4";
  ms4.location = "us.wi.madison";
  ms4.host = "host-4";
  ms4.port = 3306;
  ms4.xport = 33060;
  ms4.mode = metadata_cache::ServerMode::ReadWrite;
  ms4.role = "master";
  ms4.weight = 1;
  ms4.version_token = 0;

  ms5.replicaset_name = "replicaset-2";
  ms5.mysql_server_uuid = "instance-5";
  ms5.location = "us.wi.madison";
  ms5.host = "host-5";
  ms5.port = 3306;
  ms5.xport = 33060;
  ms5.mode = metadata_cache::ServerMode::ReadWrite;
  ms5.role = "master";
  ms5.weight = 1;
  ms5.version_token = 0;

  ms6.replicaset_name = "replicaset-2";
  ms6.mysql_server_uuid = "instance-6";
  ms6.location = "us.wi.madison";
  ms6.host = "host-6";
  ms6.port = 3306;
  ms6.xport = 33060;
  ms6.mode = metadata_cache::ServerMode::ReadOnly;;
  ms6.role = "scale-out";
  ms6.weight = 1;
  ms6.version_token = 0;

  ms7.replicaset_name = "replicaset-3";
  ms7.mysql_server_uuid = "instance-7";
  ms7.location = "us.wi.madison";
  ms7.host = "host-7";
  ms7.port = 3306;
  ms7.xport = 33060;
  ms7.mode = metadata_cache::ServerMode::ReadWrite;
  ms7.role = "master";
  ms7.weight = 1;
  ms7.version_token = 0;

  ms8.replicaset_name = "replicaset-3";
  ms8.mysql_server_uuid = "instance-8";
  ms8.location = "us.wi.madison";
  ms8.host = "host-8";
  ms8.port = 3306;
  ms8.xport = 33060;
  ms8.mode = metadata_cache::ServerMode::ReadWrite;
  ms7.role = "master";
  ms7.weight = 1;
  ms7.version_token = 0;

  ms9.replicaset_name = "replicaset-3";
  ms9.mysql_server_uuid = "instance-9";
  ms9.location = "us.wi.madison";
  ms9.host = "host-9";
  ms9.port = 3306;
  ms9.xport = 33060;
  ms9.mode = metadata_cache::ServerMode::ReadOnly;;
  ms9.role = "scale-out";
  ms9.weight = 1;
  ms9.version_token = 0;

  replicaset_1_vector.push_back(ms1);
  replicaset_1_vector.push_back(ms2);
  replicaset_1_vector.push_back(ms3);

  replicaset_2_vector.push_back(ms4);
  replicaset_2_vector.push_back(ms5);
  replicaset_2_vector.push_back(ms6);

  replicaset_3_vector.push_back(ms7);
  replicaset_3_vector.push_back(ms8);
  replicaset_3_vector.push_back(ms9);


  replicaset_map["replicaset-1"] = replicaset_1_vector;
  replicaset_map["replicaset-2"] = replicaset_2_vector;
  replicaset_map["replicaset-3"] = replicaset_3_vector;
}

/** @brief Destructor
 *
 * Disconnect and release the connection to the metadata node.
 */
MockNG::~MockNG() {}

/** @brief Returns relation between replicaset ID and list of servers
 *
 * Returns relation as a std::map between replicaset ID and list of managed servers.
 *
 * @return Map of replicaset ID, server list pairs.
 */
std::map<std::string, std::vector<metadata_cache::ManagedInstance>> MockNG::fetch_instances(const std::string &cluster_name) {
  (void)cluster_name;
  return replicaset_map;
}

/** @brief Mock connect method.
 *
 * Mock connect method, does nothing.
 *
 * @return a boolean to indicate if the connection was successful.
 */
bool MockNG::connect(const std::vector<metadata_cache::ManagedInstance>
                     & metadata_servers) noexcept {
  (void)metadata_servers;
  return true;
}

/** @brief Mock connect method.
 *
 * Mock connect method, does nothing.
 *
 * @return a boolean to indicate if the connection was successful.
 */
void MockNG::disconnect() noexcept {
}

/**
 *
 * Returns a mock refresh interval.
 *
 * @return refresh interval of the Metadata cache.
 */
unsigned int MockNG::fetch_ttl() {
  return 5;
}
