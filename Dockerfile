FROM node:20.17.0 AS build

RUN corepack enable

WORKDIR /usr/src/app
COPY ["package.json", "package-lock.json*", "npm-shrinkwrap.json*", ".yarnrc.yml", "yarn.lock", "./"]
RUN yarn

COPY . .

RUN yarn run drizzle-kit migrate
RUN yarn build

ENV PUBLIC_TIME_INTERVAL=${PUBLIC_TIME_INTERVAL}

EXPOSE 3000
CMD ["node", "build"]