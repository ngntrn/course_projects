'''

Name: Ngan Tran
Course: CS 496
Project: Final Project
File: main.py 

'''

import webapp2
from google.appengine.ext import ndb
import collections
import json

# base url of api
URL = "https://volunteer-projects-app.appspot.com/"

# project class
class Project(ndb.Model):
	id = ndb.StringProperty()
	name = ndb.StringProperty()
	date = ndb.StringProperty()
	category = ndb.StringProperty()
	location = ndb.StringProperty()
	volunteers = ndb.StringProperty(repeated = True)

# volunteer class
class Volunteer(ndb.Model):
	id = ndb.StringProperty()
	name = ndb.StringProperty()
	age = ndb.IntegerProperty()
	phone = ndb.StringProperty()
	interests = ndb.StringProperty()
	project = ndb.StringProperty()

# create a new project
def add_new_project(self):
    info = json.loads(self.request.body)
    print(info)
    if 'name' not in info or \
        'date' not in info or \
        'category' not in info or \
        'location' not in info:
                self.response.set_status = 400
                self.response.write("please include the required data fields")
                return

    new_proj = Project(name=info['name'],
                   date=info['date'],
                   category=info['category'],
                   location=info['location'],
                   volunteers=[]
                   )
    new_proj.put()
    new_proj.id = new_proj.key.urlsafe()
    new_proj.put()
    get_project_by_id(self, new_proj.id)

# get project from id
def get_project_by_id(self, id):
	project = ndb.Key(urlsafe=id).get()
	if not project:
		self.response.set_status = 400
		return
	data_dict = collections.OrderedDict()
	data_dict['id'] = str(project.id)
	data_dict['name'] = str(project.name)
	data_dict['date'] = str(project.date)
	data_dict['category'] = str(project.category)
	data_dict['location'] = str(project.location)
	data_dict['volunteers'] = project.volunteers
	data_dict['self'] = str(URL) + str("project/") + str(project.id)

	self.response.write(json.dumps(data_dict))

# returns all projects in DB
def get_all_projects(self):
	projects_list = []
	query = ndb.gql("SELECT * FROM Project")
	for project in query.fetch():
		data_dict = collections.OrderedDict()
		data_dict['id'] = str(project.id)
		data_dict['name'] = str(project.name)
		data_dict['date'] = str(project.date)
		data_dict['category'] = str(project.category)
		data_dict['location'] = str(project.location)
		data_dict['volunteers'] = project.volunteers
		data_dict['self'] = str(URL) + str("project/") + str(project.id)
		projects_list.append(data_dict)
	self.response.write(json.dumps(projects_list))

# update project
def update_project(self, id):
	project = ndb.Key(urlsafe=id).get()
	if not project:
		self.response.status_int = 404
		return
	update = json.loads(self.request.body)
	if 'name' in update:
		project.name = str(update['name'])
	else:
		project.name = project.name
	if 'date' in update:
		project.date = str(update['date'])
	else: 
		project.date = project.date
	if 'category' in update:
		project.category = str(update['category'])
	else:
		project.category = project.category
	if 'location' in update: 
		project.location = str(update['location'])
	else:
		project.location = project.location
	project.put()
	get_project_by_id(self, id)

# deletes project by id
def delete_project(self, id):
	p_delete = ndb.Key(urlsafe=id).get()
	if not p_delete:
		self.response.status_int = 404
		return

	query = ndb.gql("SELECT * FROM Volunteer where project = '" + id + "'")
	for v in query:
		v.project = None
		v.put()

	p_delete.key.delete()
	self.response.status_int = 204

# adds a new volunteer to DB
def add_volunteer(self):
    info = json.loads(self.request.body)
    print(info)
    if 'name' not in info or \
        'age' not in info or \
        'phone' not in info or \
        'interests' not in info:
                    self.response.set_status = 400
                        self.response.write("please include the required data fields")
                        return

    new_vol = Volunteer(name=info['name'],
                    age=info['age'],
                    phone=info['phone'],
                    interests=info['interests'],
                    project=None
                    )
    new_vol.put()
    new_vol.id = new_vol.key.urlsafe()
    new_vol.put()
    get_volunteer_by_id(self, new_vol.id)

# returns volunteer by id
def get_volunteer_by_id(self, id):
	vol = ndb.Key(urlsafe=id).get()
	if not vol:
		self.response.set_status = 400
		return 

	data_dict = collections.OrderedDict()
	data_dict['id'] = str(vol.id)
	data_dict['name'] = str(vol.name)
	data_dict['age'] = int(vol.age)
	data_dict['phone'] = str(vol.phone)
	data_dict['interests'] = str(vol.interests)
	data_dict['project'] = str(vol.project)
	data_dict['self'] = str(URL) + str("volunteer/") + str(vol.id)

	self.response.write(json.dumps(data_dict))

# returns all volunteers from DB
def get_all_volunteers(self):
	vols_list = []
	query = ndb.gql("SELECT * FROM Volunteer")
	for vol in query.fetch():
		data_dict = collections.OrderedDict()
		data_dict['id'] = str(vol.id)
		data_dict['name'] = str(vol.name)
		data_dict['age'] = int(vol.age)
		data_dict['phone'] = str(vol.phone)
		data_dict['interests'] = str(vol.interests)
		data_dict['project'] = str(vol.project)
		data_dict['self'] = str(URL) + str("volunteer/") + str(vol.id)
		vols_list.append(data_dict)
	self.response.write(json.dumps(vols_list))

# update volunteer info by id
def update_volunteer(self, id):
	vol = ndb.Key(urlsafe=id).get()
	if not vol:
		self.response.status_int = 404
		return
	update = json.loads(self.request.body)
	if 'name' in update:
		vol.name = str(update['name'])
	if 'age' in update:
		vol.age = int(update['age'])
	if 'phone' in update:
		vol.phone = str(update['phone'])
	if 'interests' in update: 
		vol.interests = str(update['interests'])
	vol.put()
	get_volunteer_by_id(self, id)

# delete volunteer from DB
def delete_volunteer(self, id):
	v_delete = ndb.Key(urlsafe=id).get()
	if not v_delete:
		self.response.status_int = 404
		return

	query = ndb.gql("SELECT * FROM Project where volunteers = '" + id + "'")
	for p in query:
		p.volunteers.remove(id)
		p.put()

	v_delete.key.delete()
	self.response.status_int = 204

# returns all projects and volunteers in DB
def get_all_projects_and_volunteers(self):
    projects_list = []
    query = ndb.gql("SELECT * FROM Project")
    for p in query.fetch():
        data_dict = collections.OrderedDict()
        data_dict['id'] = str(p.id)
        data_dict['name'] = str(p.name)
        data_dict['date'] = str(p.date)
        data_dict['category'] = str(p.category)
        data_dict['location'] = str(p.location)
        data_dict['volunteers'] = p.volunteers
        data_dict['self'] = str(URL) + str("project/") + str(p.id)
        projects_list.append(data_dict)
    
    vols_list = []
    query = ndb.gql("SELECT * FROM Volunteer")
    for v in query.fetch():
        data_dict = collections.OrderedDict()
        data_dict['id'] = str(v.id)
        data_dict['name'] = str(v.name)
        data_dict['age'] = int(v.age)
        data_dict['phone'] = str(v.phone)
        data_dict['interests'] = str(v.interests)
        data_dict['project'] = str(v.project)
        data_dict['self'] = str(URL) + str("volunteer/") + str(v.id)
        vols_list.append(data_dict)
    
    projects_and_vols = {}
    projects_and_vols['Projects'] = projects_list
    projects_and_vols['Volunteers'] = vols_list

    self.response.write(json.dumps(projects_and_vols))

# get all the volunteers assigned to project by id
def get_project_volunteers(self, id):
	vols = []
	project = ndb.Key(urlsafe=id).get()
	if not project:
		self.response.status_int = 404
		self.response.write("no Project found from provided id")
		return 

	query = ndb.gql("SELECT * FROM Volunteer WHERE project = '" + project.id + "'")
	for v in query:
		data_dict = collections.OrderedDict()
		data_dict['id'] = str(v.id)
		data_dict['name'] = str(v.name)
		data_dict['age'] = int(v.age)
		data_dict['phone'] = str(v.phone)
		data_dict['interests'] = str(v.interests)
		data_dict['project'] = str(v.project)
		data_dict['self'] = str(URL) + str("volunteer/") + str(v.id)
		
		vols.append(data_dict)
	self.response.write(json.dumps(vols))

# returns all volunteers are unassigned to a project
def get_unassigned_volunteers(self):
	vols_list = []
	query = ndb.gql("SELECT * FROM Volunteer WHERE project = Null")
	for v in query.fetch():
		data_dict = collections.OrderedDict()
		data_dict['id'] = str(v.id)
		data_dict['name'] = str(v.name)
		data_dict['age'] = int(v.age)
		data_dict['phone'] = str(v.phone)
		data_dict['interests'] = str(v.interests)
		data_dict['project'] = str(v.project)
		data_dict['self'] = str(URL) + str("volunteer/") + str(v.id)
		vols_list.append(data_dict)
	self.response.write(json.dumps(vols_list))

# assign a volunteer to a project
def add_volunteer_to_project(self, id):
	data = json.loads(self.request.body)
	if 'project_id' not in data:
		self.response.status_int = 400
		self.response.write("PUT request requires you provide the project_id")
		return

	proj = ndb.Key(urlsafe=str(data['project_id'])).get()
	if not proj:
		self.response.status_int = 400
		self.response.write("provided id does not patch a Project in DB")
		return

	vol = ndb.Key(urlsafe=id).get()
	if not vol:
		self.response.status_int = 400
		self.response.write("provided id does not match any Volunteers in DB")
		return 

	if vol.project == "None":
		self.response.status_int = 400
		self.response.write("this Volunteer has already been added to a Project")
		return

	vol.project = str(proj.id)
	vol.put()

	proj.volunteers.append(str(vol.id))
	proj.put()

# remove assigned volunteer from project
def remove_volunteer_from_project(self, id):
	vol = ndb.Key(urlsafe=id).get()
	if not vol:
		self.response.status_int = 400
		self.response.write("provided id does not match any Volunteers in DB")
		return 

	proj = ndb.Key(urlsafe=vol.project).get()
	if not proj:
		self.response.status_int = 400
		self.response.write("project id is invalid")
		return

	proj.volunteers.remove(vol.id)
	vol.project = None			
	proj.put()
	vol.put()


# handlers

class MainPage(webapp2.RequestHandler):
	def get(self):
		get_all_projects_and_volunteers(self)

class ProjectHandler(webapp2.RequestHandler):
	def post(self):
		add_new_project(self)
	def get(self, id=None):
		if id:
			get_project_by_id(self, id)
		else:
			get_all_projects(self)
	def patch(self, id=None):
		if id:
			update_project(self, id)
		else:
			return 
	def delete(self, id=None):
		# if id is provided deleted the project
		if id:
			delete_project(self, id)
		else:
			return 	

class VolunteerHandler(webapp2.RequestHandler):
	def post(self):
		add_volunteer(self)
	def get(self, id=None):
		if id:
			get_volunteer_by_id(self, id)
		else:
			get_all_volunteers(self)

	def patch(self, id=None):
		if id:
			update_volunteer(self, id)
		else:
			return 

	def delete(self, id=None):
		if id:
			delete_volunteer(self, id)
		else:
			return 
	def put(self, id=None):
		if id:
			add_volunteer_to_project(self, id)
		else:
			return 

class RemoveVolunteerHandler(webapp2.RequestHandler):
	def patch(self, id=None):
		if id:
			remove_volunteer_from_project(self,id)
		else: 
			return 

class ProjectVolunteersHandler(webapp2.RequestHandler):
	def get(self, id=None):
		if id:
			get_project_volunteers(self, id)
		else:
			return 	

	def patch(self, id=None):
		if id:
			remove_volunteer_from_project(self, id)
		else:
			return 

class FreeVolunteersHandler(webapp2.RequestHandler):
	def get(self):
		get_unassigned_volunteers(self)


class ProjectVolunteerRemoveHandler(webapp2.RequestHandler):
	def patch(self, id=None):
		if id:
			remove_volunteer_from_project(self, id)
		else:
			return 

# allow for PATCH
allowed_methods = webapp2.WSGIApplication.allowed_methods
new_allowed_methods = allowed_methods.union(('PATCH',))
webapp2.WSGIApplication.allowed_methods = new_allowed_methods

app = webapp2.WSGIApplication(
	[
    ('/', MainPage),
    ('/project', ProjectHandler),
    ('/project/(.*)', ProjectHandler),
    ('/volunteer', VolunteerHandler),
    ('/volunteer/(.*)', VolunteerHandler),
    ('/no_project', FreeVolunteersHandler),
    ('/(.*)', ProjectVolunteersHandler),
	], debug=True)
