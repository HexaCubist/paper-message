FROM node:20.17.0 AS build

RUN corepack enable

WORKDIR /usr/src/app
COPY ["package.json", "package-lock.json*", "npm-shrinkwrap.json*", ".yarnrc.yml", "yarn.lock", "./"]
RUN yarn

COPY . .


ARG PUBLIC_TIME_INTERVAL=${PUBLIC_TIME_INTERVAL}
ENV PUBLIC_TIME_INTERVAL=${PUBLIC_TIME_INTERVAL}
ARG DELIVER_TIME=${DELIVER_TIME}
ENV DELIVER_TIME=${DELIVER_TIME}
ARG TZ=${TZ}
ENV TZ=${TZ}
ARG AUTH_DRIZZLE_URL=${AUTH_DRIZZLE_URL}
ENV AUTH_DRIZZLE_URL=${AUTH_DRIZZLE_URL}
RUN yarn run drizzle-kit migrate
RUN yarn build

EXPOSE 3000
CMD ["node", "build"]