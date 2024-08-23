FROM ghcr.io/puppeteer/puppeteer:21.0.1 AS build

USER root

RUN corepack enable

# Add user so we don't need --no-sandbox.
RUN mkdir -p /home/pptruser/Downloads /app \
    && chown -R pptruser:pptruser /home/pptruser \
    && chown -R pptruser:pptruser /app

# Run everything after as non-privileged user.
USER pptruser

WORKDIR /app
COPY --chown=pptruser:pptruser ["package.json", "package-lock.json*", "npm-shrinkwrap.json*", ".yarnrc.yml", "yarn.lock", "./"]
RUN cp -r /home/pptruser/node_modules ./node_modules
RUN yarn

COPY --chown=pptruser:pptruser . .

RUN ls -la

RUN yarn build

EXPOSE 3000
CMD yarn run drizzle-kit migrate && node build