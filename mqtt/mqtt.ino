#include <SPI.h>
#include <WiFi101.h>

// WiFi 网络的 SSID 和 密码
char ssid[] = "CE-Hub-Student";     // 替换为你的WiFi网络的SSID
char pass[] = "casa-ce-gagarin-public-service"; // 替换为你的WiFi网络的密码

int status = WL_IDLE_STATUS;  // 用于存储WiFi连接状态

void setup() {
  // 初始化串行通信
  Serial.begin(115200);
  while (!Serial) {
    ; // 等待串行端口连接。仅用于板子上有原生USB的板子
  }

  // 检查WiFi模块是否存在
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true); // 无法继续，停止程序
  }

  // 尝试连接到WiFi网络
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

    // 等待10秒再尝试重新连接
    delay(10000);
  }

  // 连接成功
  Serial.println("Connected to WiFi network");
  printWiFiStatus();
}

void loop() {
  // 在此处编写你的代码
}

// 打印WiFi状态
void printWiFiStatus() {
  // 打印SSID
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // 打印板子的IP地址
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // 打印信号强度
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
}
