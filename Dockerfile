FROM ghcr.io/puppeteer/puppeteer:23 AS build

USER root

# Add user so we don't need --no-sandbox.
RUN mkdir -p /home/pptruser/Downloads /app \
    && chown -R pptruser:pptruser /home/pptruser \
    && chown -R pptruser:pptruser /app

# Run everything after as non-privileged user.
USER pptruser

RUN corepack enable

WORKDIR /app
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
RUN yarn build

EXPOSE 3000
CMD yarn run drizzle-kit migrate && node build