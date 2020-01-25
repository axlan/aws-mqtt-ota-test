import boto3
import json
import os
import logging
logger = logging.getLogger()
logger.setLevel(logging.INFO)

client = boto3.client('iot-data', region_name='us-west-1')

def publish_to_threehouseslights():
    # Change topic, qos and payload
    return client.publish(
            topic='$aws/things/threehouseslights/shadow/update',
            qos=1,
            payload=json.dumps({"foo":"bar"})
        )

def lambda_handler(event, context):
    body = event.get("body", None)
    if body != None:
        data = json.loads(body)
        auth_attempt = data.get('REQUEST_AUTH_TOKEN', None)
    else:
        auth_attempt = None
    auth = os.environ.get('REQUEST_AUTH_TOKEN', None)
    if auth is None or auth_attempt is None:
        return {'statusCode': 200}
    if auth_attempt != auth:
        logger.warn('Invalid auth token')
        return {
            'statusCode': 401,
            'body': 'Invalid auth token'
        }
    logger.info('Request')
    response = publish_to_threehouseslights()
    
    return {
        'statusCode': 200,
        'body': json.dumps(response),
        "headers": {
            'Content-Type': 'application/json'
        }
    }
