import webapp2
from google.appengine.ext.webapp import template
from google.appengine.api import urlfetch
import os
import urllib
import random
import string
import json

ID ='121869829202-6utemud5keb0mrmqv8tifsokm3d68ndt.apps.googleusercontent.com'
SECRET = 'BZU6qcIq6jEg2uqomZ6Eva1a'
REDIRECT_URI = 'https://oauth2-impl.appspot.com/oauth'

class MainPage(webapp2.RequestHandler):
    def get(self):
        # create a random string for the state value 
        random_str = ''.join([random.choice(string.ascii_letters + string.digits) for n in xrange(32)])
        link_text = 'Provide Access'
        # create link to authorize access to account info 
        link = "https://accounts.google.com/o/oauth2/v2/auth?"
        link = link + "scope=email&access_type=offline&include_granted_scopes=true&state="
        link = link + random_str
        link = link + "&redirect_uri=" + REDIRECT_URI
        link = link + "&response_type=code"
        link = link + "&client_id=" + ID

        # Django template
        template_values = {'url': link}
        # get user's authorization, send to authorization URL
        path = os.path.join(os.path.dirname(__file__), 'home.html')
        self.response.out.write(template.render(path, template_values))

class OAuthHandler(webapp2.RequestHandler):
    def get(self):
        
        #get authorization code recieved from initial authorize call
        a_code = self.request.GET['code']
        state = self.request.GET['state']
        
        data = {
            'grant_type': 'authorization_code',
            'client_id': ID,
            'client_secret': SECRET,
            'code': a_code,
            'redirect_uri': REDIRECT_URI
            }

        payload = urllib.urlencode(data)
        headers = {'Content-Type':'application/x-www-form-urlencoded'}
        # using authorization code that was retrieved, POST to the token URL
        # exchanging the authorization code for an access token
        result = urlfetch.fetch(
            url="https://www.googleapis.com/oauth2/v4/token",
   		 	payload = payload,
    		method = urlfetch.POST,
    		headers = headers)
    		
        # load the results to get the access token
        json_result = json.loads(result.content)

        # pass bearer token and access token in message header 
        headers = {'Authorization': 'Bearer ' + json_result['access_token']}
        # fetch the user's account info from googleapi 
        result = urlfetch.fetch(
            url="https://www.googleapis.com/plus/v1/people/me",
            method = urlfetch.GET,
            headers=headers)
        
        # search through response json for account information 
        json_result = json.loads(result.content)
        # flags to determine if info is found
        found_f_name = found_l_name = found_profile = found_account = False
        for item in json_result:
            if item == 'name':
                if item[0]:
                    found_f_name = True
                    found_l_name = True
            if item == 'url':
                found_profile = True

        # if the account info is retrieved
        if found_f_name and found_l_name and found_profile:
            f_name = json_result['name']['givenName']
            l_name = json_result['name']['familyName']
            profile = str(json_result['url'])
            found_account = True
            # add found values to template
            template_values = {'f_name': f_name,
                               'l_name': l_name,
                               'profile': profile,
                               'profile_link': "Link",
                               'state': state}
        
        # G+ account was not found
        else:
            template_values = {'notFound': "Google+ account was not found", 'state': state}

        path = os.path.join(os.path.dirname(__file__), 'oauth.html')
        # send values and redirect to results page 
        self.response.out.write(template.render(path, template_values))

app = webapp2.WSGIApplication([
    ('/', MainPage),
    ('/oauth',OAuthHandler)
], debug=True)
