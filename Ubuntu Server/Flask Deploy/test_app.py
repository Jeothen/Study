import pytest
from app import app

@pytest.fixture
def client():
	return app.test_client()

def do_get(client,path):
	response = client.get(path)
	return response.status_code, str(response.data), response.get_json()

# def test_sample() :
	# import 한 app	
	# pytest에서 parameter로 설정 가능
	# client = app.test_client()
def test_sample(client):	

	status_code, body, data = do_get(client,'/json')
	assert status_code == 200
	assert '"test":"SUCCESS"' in body
	
#	response = client.get('/')
#	assert response.status_code == 200
#	# transform byte code -> b""	
#	assert b'Suc' in response.data	
#	data = response.get_json()

	old_cnt = data["count"]
	
	status_code, body, data = do_get(client,'/json')
	assert status_code == 200
	new_cnt = data["count"]
	assert old_cnt + 1 == new_cnt


