FROM node:20.17.0 AS build

WORKDIR /usr/src/app
COPY ["package.json", "package-lock.json*", "npm-shrinkwrap.json*", ".yarnrc.yml", "yarn.lock", "./"]
RUN yarn

COPY . .
RUN yarn build

ENV PUBLIC_TIME_INTERVAL=${PUBLIC_TIME_INTERVAL}

EXPOSE 3000
CMD ["node", "build"]