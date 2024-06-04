### Deploying a jar file to Heroku:

- heroku plugins:install heroku-cli-deploy
- heroku login
- heroku deploy:jar .../target/myproject.jar --app HEROKU_APP_NAME