import requests

url="https://momiji.hiroshima-u.ac.jp/syllabusHtml/"
url_home=url+"2024_15.html"
response = requests.get(url_home)
syllabus_home = response.text

from bs4 import BeautifulSoup

soup = BeautifulSoup(syllabus_home, "html.parser")
links = []
kamoku_data_cells = soup.find_all("td", class_="kamoku-data")
for cell in kamoku_data_cells:
	link = cell.find("a")
	if link:
		href_value = link.get("href")
		links.append(url+href_value)

class_list = []
for clas in links:
  res=requests.get(clas)
  res.encoding='utf-8'
  syllc=res.text
  with open("syll/"+clas.replace(url,"").replace(".html","")+".txt","w",encoding='utf-8') as file:
    file.write(syllc)
