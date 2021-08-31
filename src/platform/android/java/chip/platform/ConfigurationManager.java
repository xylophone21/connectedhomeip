/*
 *   Copyright (c) 2021 Project CHIP Authors
 *   All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */
package chip.platform;

/**
 * Java interface for ConfigurationManager
 */
public interface ConfigurationManager {
    long readConfigValueLong(String namespace, String name);
    String readConfigValueStr(String namespace, String name);
    byte[] readConfigValueBin(String namespace, String name);
    void writeConfigValueLong(String namespace, String name, long val);
    void writeConfigValueStr(String namespace, String name, String val);
    void writeConfigValueBin(String namespace, String name, byte[] val);
    void clearConfigValue(String namespace, String name);
    boolean configValueExists(String namespace, String name);
}
