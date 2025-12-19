Dockerfile
# Base image
FROM node:lts-alpine3.23 

#Copy files
COPY index.js .

COPY package.json .

# install packages
RUN npm install
CMD ["node","index1.js"]