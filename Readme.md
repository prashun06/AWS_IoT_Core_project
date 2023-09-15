First code tested by MQTT test client panel<br>

## 1. Push Notification to Mobile(SMS) from AWS 
First create rule from message route->action SNS(create SNS service)->Create IAM rule->create (There are more settings)
SQL statement <br> 
SELECT * FROM 'AWS-IoT' = AWS-IoT is the topic = Row data send to mobile message(Json formate also can be implemente) using AWS SNS.<br>
Role set (IAM) mytextRule attached from policies and route the subscribed topic masssage to the SMS of my own number.

<p align="center">
  <img src="https://github.com/prashun06/AWS_IoT_Core_project/blob/main/Images/SNS.png" alt="AWS Message routing panal"/>
</p>
<p align="center">
  <img src="https://github.com/prashun06/AWS_IoT_Core_project/blob/main/Images/text%20Mesg.jpg" width="30%" height="10%" />
</p>

## 1. Save the json data into S3 bucket

First create rule from message route->action S3(create a bucket (public access to keep simple now))->key(the name of file)->Create IAM rule->create <br> 
[Json for Bucket policy here](https://github.com/prashun06/AWS_IoT_Core_project/blob/main/policy_json.json/)

